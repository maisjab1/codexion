#include "codexion.h"
void* routine(void* arg)
{
	t_coder *coder = (t_coder *) arg;
	t_state *state = coder->state;
	t_dongle *first ;	
	t_dongle *second ;	
	while(coder->number_of_compiles < state->config->number_of_compiles_required)
	{
		if (state->someone_starved)
            		return NULL;
		// asymmetric pickup
		first = (coder->id % 2 == 0)  ?  coder->left :coder->right
		second = (coder->id % 2 == 0)  ? coder->right :coder->left
		// try to get first dongle
        	// if got it, try second
        	// if got both: work, release, repeat
        	// if not: check starvation, release first if needed
	}
	return NULL;
}
