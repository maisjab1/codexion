#include "codexion.h"

void clean_up(t_state *state)
{
    free(state->coders);
    free(state->config);
    free(state->dongles);
}
