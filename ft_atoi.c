/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:46:54 by nainhaja          #+#    #+#             */
/*   Updated: 2019/10/22 22:19:50 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_espace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
	{				
		i++;
		while (str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
			i++;
	}
	return (i);
}

static long	ft_countnb(const char *str, long j)
{
	while (ft_isdigit(str[j]) == 1)
		j++;
	return (j);
}

static long	ft_nret(char const *str, long cpt, long j)
{
	long	cpt2;
	long	n;

	cpt2 = 1;
	n = 0;
	while (cpt >= j)
	{
		n = n + (cpt2 * (str[cpt] - '0'));
		cpt2 = cpt2 * 10;
		cpt--;
	}
	return (n);
}

long	ft_atoi(const char *str)
{
	long	j;
	long	cpt;
	long	n;

	n = 1;
	j = ft_espace(str);
	if (str[j] == '-')
	{
		n = (-1);
		j++;
	}
	else if (str[j] == '+')
		j++;
	cpt = ft_countnb(str, j);
	if (cpt == j)
		return (0);
	cpt = cpt - 1;
	n = n * (ft_nret(str, cpt, j));
	if (n > (long)2147483647 || n < (long) -2147483648)
	{
		return (-1);
	}
	return (n);
}
