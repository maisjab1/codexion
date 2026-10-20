/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabarin <mjabarin@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 16:39:54 by mjabarin          #+#    #+#             */
/*   Updated: 2026/10/16 16:31:54 by mjabarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

int	main(int argc, char **argv)
{
//	t_config	*config;
	t_state		state;
    pthread_t   monitor;
	int 	i;


	state.config = malloc(sizeof(t_config));
	memset(state.config, 0, sizeof(t_config));
	if (argc != 9)
	{
		printf("Incorrect number of arguments\n");
		return (0);
	}
	if (!validate(argv))
		return(0);
	init_config(argv, state.config);
    int (*cmp)(t_request *, t_request *) = cmp_fifo;
    if (strcmp(state.config->scheduler, "edf") == 0)
        cmp = cmp_edf;   

// array allocate + init
	state.coders = malloc(sizeof(t_coder) * state.config ->number_of_coders);
	state.dongles = malloc(sizeof(t_dongle) * state.config ->number_of_coders);
	i = 0;
	while ( i < state.config ->number_of_coders)
	{
		pthread_mutex_init(&state.dongles[i].mutex, NULL);
        pthread_cond_init(&state.dongles[i].cond, NULL);
		state.dongles[i].id = i + 1;
		state.dongles[i].taken = 0;
        state.dongles[i].pq= malloc(sizeof(t_pq));
        init_queue(state.dongles[i].pq, cmp);
		clock_gettime(CLOCK_MONOTONIC,&state.dongles[i].release_start);
		i++;
	}
	pthread_mutex_init(&state.print_mutex,NULL);
    pthread_mutex_init(&state.mutex,NULL);
	i = 0;
	while ( i < state.config ->number_of_coders)
	{
	state.coders[i].state=&state;
		state.coders[i].id = i + 1;
		clock_gettime(CLOCK_MONOTONIC, &state.coders[i].wait_start);
		state.coders[i].num_of_compiles = 0;
		state.coders[i].left = &state.dongles[i];
		state.coders[i].right = &state.dongles[(i + 1) % state.config->number_of_coders];
        state.coders[i].compilation_start = 0;
		i++;
	}
	
	clock_gettime(CLOCK_MONOTONIC, &state.start_time);
	state.someone_starved = false;
// threads
// monitor

    pthread_create(&monitor, NULL, monitor_routine,&state);
    pthread_join(monitor, NULL);
// coders
    i = 0;
	while ( i < state.config ->number_of_coders)
	{
		if (pthread_create(&state.coders[i].thread, NULL, routine,&state.coders[i]) != 0)
			fprintf(stderr, "Failed to create thread");
		i++;
	}
	i = 0;
	while ( i < state.config ->number_of_coders)
	{
		if (pthread_join(state.coders[i].thread, NULL) != 0)
			fprintf(stderr,"Failed to join thread");
		i++;
	}
    clean_up(&state);
	return 0;
}
