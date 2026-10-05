/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabarin <mjabarin@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 17:10:20 by mjabarin          #+#    #+#             */
/*   Updated: 2026/09/20 14:57:02 by mjabarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
int ft_isdigit(int c)
{
	if (!(c >='0' && c <='9'))
		return (0);
	return(1);
}

int ft_isnum(char *num)
{
	int i;
	i = 0;
	if (!num || !*num)
	{
		printf("Error\n");
		return(0);
	}
	if (num[i] == '-')
	{
		printf("Error negative value\n");
		return(0);
	}
	if (num[i] =='+')
		i++;
	if (num[i] == '0')
	{
		printf("value should be over 0\n");
		return (0);
	}
	if (!num[i])
	{
		printf("Error\n");
		return (0);
	}
	while(num[i])
	{
		if (!ft_isdigit(num[i]))
		{		
			printf("Argument (1-7) needs to be an int\n");
			return(0);
		}
		i++;
	}
	return(1);
}


int validate(char **argv)
{
	int i;
	i = 1;
	while (argv[i])
	{
		if (i == 8)
                        break;
		if (!ft_isnum(argv[i]))
			return (0);
		i++;
	}
	if (!strcmp(argv[8],"fifo") == 0 && !strcmp(argv[8],"edf") == 0)
	{
			printf("invalid scheduler\n");
			return (0);
	}
	return (1);	

}
