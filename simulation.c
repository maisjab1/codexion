#include "codexion.h"
bool try_to_get(t_dongle *dongle,t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->taken)
	{	 
		pthread_mutex_unlock(&dongle->mutex);
        	return false;
	}
	else
	{
		dongle->taken =true;
		pthread_mutex_unlock(&dongle->mutex);
		printf("%ld %d has taken a dongle\n", get_elapsed_ms(coder->state->start_time), coder->id);
		return true;
	}
}

void	release(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
    	dongle->taken = false;
    	clock_gettime(CLOCK_MONOTONIC, &dongle->release_start);
    	pthread_mutex_unlock(&dongle->mutex);

}

void	work(t_coder *coder)
{	
	printf("%ld %d is compiling\n", get_elapsed_ms(coder->state->start_time), coder->id);
	coder->num_of_compiles++;
	printf("%ld %d is debugging\n", get_elapsed_ms(coder->state->start_time), coder->id);
	printf("%ld %d is refactoring\n", get_elapsed_ms(coder->state->start_time), coder->id);
	release(coder->left);
	release(coder->right);
}
void* routine(void* arg)
{
	t_coder *coder = (t_coder *) arg;
	t_state *state = coder->state;
	t_dongle *first ;	
	t_dongle *second ;	
	while(coder->num_of_compiles < state->config->number_of_compiles_required)
	{
		if (state->someone_starved)
            		return NULL;
		// asymmetric pickup
		first = (coder->id % 2 == 0)  ?  coder->left :coder->right;
		second = (coder->id % 2 == 0)  ? coder->right :coder->left;
		// try to get first dongle
		clock_gettime(CLOCK_MONOTONIC, &coder->wait_start);
		if (get_elapsed_ms(coder->wait_start) > state->config->time_to_burnout)
		{
			state->someone_starved =true;
			printf("%ld %d burned out\n", get_elapsed_ms(coder->state->start_time), coder->id);
			return NULL;
		}
		if (try_to_get(first,coder))
		{
			if(try_to_get(second,coder))
				work(coder);
			else
				release(first);
		}
        	// if got it, try second
        	// if got both: work, release, repeat
        	// if not: check starvation, release first if needed
	}
	return NULL;
}
