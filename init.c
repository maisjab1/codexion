#include "codexion.h"

void init_config(int argc ,char **argv,t_config *config)
{
	config -> number_of_coders = atoi(argv[1]);
	config -> time_to_burnout = atoi(argv[2]);
	config -> time_to_compile = atoi(argv[3]);
	config -> time_to_debug = atoi(argv[4]);
	config -> time_to_refactor = atoi(argv[5]);
	config-> number_of_compiles_required = atoi(argv[6]);
	config -> dongle_cooldown = atoi(argv[7]);
	config -> scheduler= argv[8];
}

