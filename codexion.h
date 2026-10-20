#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include<unistd.h>
#include <time.h>

typedef enum e_scheduler
{
	FIFO,
	EDF,
} t_scheduler;

typedef struct s_pq t_pq;
typedef struct s_state t_state;  // forward declaration
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
    pthread_cond_t  cond;
	unsigned int id;
	bool taken;
	struct timespec release_start;
    t_pq *pq;
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
}t_coder;

typedef struct s_state
{
    pthread_mutex_t print_mutex;
    pthread_mutex_t mutex;
	t_coder *coders;
	t_dongle *dongles;
	t_config *config;
	struct timespec start_time;
	bool someone_starved;
    unsigned int req_counter;
} t_state;

typedef struct s_request
{
	unsigned int	coder_id;
	long			deadline;
	unsigned long	arrival_order;
}	t_request;

typedef struct s_node
{
    int index;
    struct s_node *parent;
    struct s_node *left;
    struct s_node *right;
    t_request      req;
}   t_node;

typedef struct s_pq
{
	t_node *head;
	int	size;
    int    (*cmp)(t_request *, t_request *);
}  t_pq;

int validate(char **argv);
void* routine(void* arg);
void init_config(char **argv, t_config *config);
long get_elapsed_ms(struct timespec start);
bool try_to_get(t_dongle *dongle,t_coder *coder, t_state *state);
void release(t_dongle *dongle);
void work(t_coder *coder);
void		init_queue(t_pq *q, int (*cmp)(t_request *, t_request *));
void		insert(t_pq *q, t_request req);
int extract(t_pq *q, t_request *req);
t_request	peek(t_pq *q);
int			cmp_fifo(t_request *r1, t_request *r2);
int			cmp_edf(t_request *r1, t_request *r2);
void    clean_up(t_state *state);
