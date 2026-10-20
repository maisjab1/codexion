#include "codexion.h"

void clean_up_dongles(t_state *state)
{
    int i;
    t_request tmp;

    i = 0;
    while(i < state->config->number_of_coders)
    {
        while(extract(state->dongles[i].pq, &tmp))
            ;
        free(state->dongles[i].pq);
        pthread_mutex_destroy(&state->dongles[i].mutex);
        pthread_cond_destroy(&state->dongles[i].cond);
        i++;
    }
}
void clean_up(t_state *state)
{
    free(state->coders);
    clean_up_dongles(state);
    free(state->dongles);

    pthread_mutex_destroy(&state->print_mutex);
    pthread_mutex_destroy(&state->mutex);
    free(state->config);
}
