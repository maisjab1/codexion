#include "codexion.h"
#include <stdbool.h>

bool try_to_get(t_dongle *dongle,t_coder *coder,t_state *state)
{
    t_request req;
    t_request head;

    req.coder_id = coder->id;
    pthread_mutex_lock(&state->mutex);

    req.arrival_order = state->req_counter++;
    req.deadline = coder->compilation_start + state->config->time_to_burnout; 
    pthread_mutex_unlock(&state->mutex);

	pthread_mutex_lock(&dongle->mutex);
    insert(dongle->pq, req); 
    while (!coder->state->someone_starved)
    {
        head = peek(dongle->pq);
        if (head.coder_id == coder->id &&
            !dongle->taken && 
            (coder->num_of_compiles == 0 ||
            get_elapsed_ms(dongle->release_start) >= coder->state->config->dongle_cooldown))
            break;
        if (head.coder_id == coder->id && !dongle->taken)   /* head, free, but cooling */
        {
            pthread_mutex_unlock(&dongle->mutex);
            usleep(1000);
            pthread_mutex_lock(&dongle->mutex);
            continue;
        }
        if (coder->state->config->number_of_coders > 1)
            pthread_cond_wait(&dongle->cond,&dongle->mutex);
        else
        {
            pthread_mutex_unlock(&dongle->mutex);
            return(false);
        }
    }
    if (coder->state->someone_starved)
    {
        pthread_mutex_unlock(&dongle->mutex);
        return (false);
    }
    dongle->taken =true;
    extract(dongle->pq, &req);
    pthread_mutex_unlock(&dongle->mutex);
    printf("%ld %d has taken a dongle\n", get_elapsed_ms(coder->state->start_time), coder->id);
    return true;
}

void	release(t_dongle *dongle)
{
	    pthread_mutex_lock(&dongle->mutex);
    	dongle->taken = false;
    	clock_gettime(CLOCK_MONOTONIC, &dongle->release_start);
        pthread_cond_broadcast(&dongle->cond);
        pthread_mutex_unlock(&dongle->mutex);
}

void	work(t_coder *coder)
{	
	if (coder->state->someone_starved) return;
    coder->compilation_start = get_elapsed_ms(coder->state->start_time);
    clock_gettime(CLOCK_MONOTONIC, &coder->wait_start);
    
    pthread_mutex_lock(&coder->state->print_mutex);
	printf("%ld %d is compiling\n", get_elapsed_ms(coder->state->start_time), coder->id);
	pthread_mutex_unlock(&coder->state->print_mutex);
	
    coder->num_of_compiles++;
	usleep(coder->state->config->time_to_compile * 1000);
	release(coder->left);
	release(coder->right);
	if (coder->state->someone_starved) return;
	
    pthread_mutex_lock(&coder->state->print_mutex);
	printf("%ld %d is debugging\n", get_elapsed_ms(coder->state->start_time), coder->id);
	pthread_mutex_unlock(&coder->state->print_mutex);
	
    usleep(coder->state->config->time_to_debug * 1000);
	if (coder->state->someone_starved) return;
    
    pthread_mutex_lock(&coder->state->print_mutex);
	printf("%ld %d is refactoring\n", get_elapsed_ms(coder->state->start_time), coder->id);
	pthread_mutex_unlock(&coder->state->print_mutex);
	
    usleep(coder->state->config->time_to_refactor * 1000);
	if (coder->state->someone_starved) return;
	
}
void* routine(void* arg)
{
	t_coder *coder = (t_coder *) arg;
	t_state *state = coder->state;
	t_dongle *first ;	
	t_dongle *second ;
	clock_gettime(CLOCK_MONOTONIC, &coder->wait_start);
//	printf("%ld ",&coder->wait_start);
	while(coder->num_of_compiles < state->config->number_of_compiles_required)
	{
		if (state->someone_starved)
            		return NULL;
		// asymmetric pickup
		first = (coder->id % 2 == 0)  ?  coder->left :coder->right;
		second = (coder->id % 2 == 0)  ? coder->right :coder->left;
		// try to get first dongle
		if (get_elapsed_ms(coder->wait_start) > state->config->time_to_burnout)
		{
            pthread_mutex_lock(&coder->state->mutex);
			state->someone_starved = true;
            pthread_mutex_unlock(&coder->state->mutex);
            
            pthread_mutex_lock(&coder->state->print_mutex);
			printf("%ld %d burned out\n", get_elapsed_ms(coder->state->start_time), coder->id);
            pthread_mutex_unlock(&coder->state->print_mutex);
			return NULL;
		}
		if (try_to_get(first,coder,state))
		{
			if(try_to_get(second,coder,state))
			{
				work(coder);
				//printf("%ld ",&coder->wait_start);
			}
			else
				release(first);
		}
        	// if got it, try second
        	// if got both: work, release, repeat
        	// if not: check starvation, release first if needed
		// sleep to wait before retrying to take the dongles prevents busy-waiting
		usleep(1000);
	}
	return NULL;
}
