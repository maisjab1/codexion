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
	t_config	*config;
	int 	i;
	pthread_t th[4];

	i = 0;
	config = malloc(sizeof(t_config));
	memset(config, 0, sizeof(t_config));
	if (argc != 9)
	{
		printf("Incorrect number of arguments\n");
		return (0);
	}
	if (!validate(argv))
		return(0);
	init_config(argc, argv, config);
// threads
	while ( i < config ->number_of_coders)
	{
		if (pthread_create(&th[i], NULL, routine,NULL) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while ( i < config ->number_of_coders)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	
	/*
	printf("%d\n",config->number_of_coders);
	printf("%d\n",config->time_to_burnout);
	printf("%d\n",config->time_to_compile);
	printf("%d\n",config->time_to_debug);
	printf("%d\n",config->time_to_refactor);
	printf("%d\n",config->number_of_compiles_required);
	printf("%d\n",config->dongle_cooldown);
	printf("%s\n",config->scheduler);
	*/
	return 0;
}
