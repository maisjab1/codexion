/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabarin <mjabarin@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 16:39:54 by mjabarin          #+#    #+#             */
/*   Updated: 2026/09/14 17:22:03 by mjabarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	main(int argc, char **argv)
{
	if (argc != 9)
	{
		printf("Incorrect argument count");
		return (0);
	}
	validate(argv);
	return 0;
}
