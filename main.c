/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabarin <mjabarin@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 16:39:54 by mjabarin          #+#    #+#             */
/*   Updated: 2026/09/26 18:58:59 by mjabarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	main(int argc, char **argv)
{
//	t_config	*config;
	t_state		state;
	int 	i;
	pthread_t th[4];

	state.config = malloc(sizeof(t_config));
	memset(state.config, 0, sizeof(t_config));
	if (argc != 9)
	{
		printf("Incorrect number of arguments\n");
		return (0);
	}
	if (!validate(argv))
		return(0);
	init_config(argc, argv, state.config);

// array allocate + init
	state.coders = malloc(sizeof(t_coder) * state.config ->number_of_coders);
	state.dongles = malloc(sizeof(t_dongle) * state.config ->number_of_coders);
	i = 0;
	while ( i < state.config ->number_of_coders)
	{
		pthread_mutex_init(&state.dongles[i].mutex, NULL);
		state.dongles[i].id = i;
		state.dongles[i].taken = 0;
		state.dongles[i].release_start = 0;
		i++;
	}
	i = 0;
	while ( i < state.config ->number_of_coders)
	{
		//pthreadd_create(&state.coders[i].thread,NULL, routine ,NULL)
		state.coders[i].id = i;
		state.coders[i].time_to_burnout = 0;
		state.coders[i].num_of_compiles = 0;
		state.coders[i].left = &state.dongles[i];
		state.coders[i].right = &state.dongles[(i + 1) % state.config->number_of_coders];
		i++;
	}

// threads
	i = 0;
	while ( i < state.config ->number_of_coders)
	{
		if (pthread_create(&state.coders[i].thread, NULL, routine,&state) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while ( i < state.config ->number_of_coders)
	{
		if (pthread_join(state.coders[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
		
	return 0;
}
