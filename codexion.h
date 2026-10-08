#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include<unistd.h>
#include <time.h>


//structs
typedef struct s_config
{
	int number_of_coders;
	int time_to_burnout;
	int time_to_compile;
	int time_to_debug;
	int time_to_refactor;
	int number_of_compiles_required;
	int dongle_cooldown;
	char* scheduler;
} t_config;


typedef struct s_dongle
{
	pthread_mutex_t mutex;
	unsigned int id;
	bool taken;
	int release_start;
} t_dongle;

typedef struct s_coder
{
	t_state	*state; 
	pthread_t thread;
	struct timespec wait_start;
	int num_of_compiles;
	unsigned int id;
	t_dongle *left;
	t_dongle *right;
	int compilation_start;
} t_coder;

typedef struct s_state
{
	t_coder *coders;
	t_dongle *dongles;
	t_config *config;
	struct timespec start_time;
	bool someone_starved;
} t_state;

int validate(char **argv);
void* routine(void* arg);
void init_config(int argc ,char **argv, t_config *config);
long get_elapsed_ms(struct timespec start);
