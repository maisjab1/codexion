/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabarin <mjabarin@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 18:05:39 by mjabarin          #+#    #+#             */
/*   Updated: 2026/10/20 18:05:40 by mjabarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int cmp_fifo(t_request *r1, t_request *r2)
{
    if (r1->arrival_order > r2->arrival_order)
        return(1);
    if (r1->arrival_order < r2->arrival_order)
        return(-1);
    else 
        return(0);
}

int cmp_edf(t_request *r1, t_request *r2)
{
    if (r1->deadline > r2->deadline)
        return(1);
    if (r1->deadline < r2->deadline)
        return(-1);
    else 
        return ((r1->arrival_order > r2->arrival_order)
		- (r1->arrival_order < r2->arrival_order));
}

