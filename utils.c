/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabarin <mjabarin@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 18:05:46 by mjabarin          #+#    #+#             */
/*   Updated: 2026/10/20 18:05:47 by mjabarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long get_elapsed_ms(struct timespec start)
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);	
	return ((now.tv_sec - start.tv_sec )*1000 +(now.tv_nsec - start.tv_nsec)/ 1000000);
}
