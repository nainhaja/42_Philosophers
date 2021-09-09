/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:36:45 by nainhaja          #+#    #+#             */
/*   Updated: 2021/09/07 18:36:46 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_checkstring(char *str)
{
	int	i;
	int	size;
	int	flag;

	i = 0;
	size = ft_strlen(str);
	flag = 1;
	while (i < size)
	{
		if (ft_isdigit(str[i]) == 0)
			flag = 0;
		i++;
	}
	return (flag);
}

void	last_check(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_checkstring(argv[i]) == 0)
		{
			argv[i] = "-1";
			break ;
		}
		i++;
	}
}

void	check_arg(char **argv, int argc, struct t_philo *philo)
{
	if (argc == 6)
		philo->m->nb_meals = ft_atoi(argv[5]);
	else
		philo->m->nb_meals = -1;
	philo->m->time_todie = ft_atoi(argv[2]);
	philo->m->nb = ft_atoi(argv[1]);
}

int	ft_checkminus(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == -1
			|| ft_checkstring(argv[i]) == 0 || ft_strlen(argv[i]) == 0)
		{
			printf("Error in arguments \n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	struct t_philo	*philo;
	t_mutexes		*m;

	m = malloc(sizeof(t_mutexes));
	if (argc == 5 || argc == 6)
	{
		if (ft_checkminus(argv, argc) == 0 || ft_atoi(argv[1]) == 0)
			return (0);
		philo = malloc(sizeof(t_ph) * ft_atoi(argv[1]));
		init(philo, m, ft_atoi(argv[1]));
		data(ft_atoi(argv[1]), philo, argv, m);
		check_arg(argv, argc, philo);
		if (philo->m->nb == 0)
			return (1);
		philo->m->flag = 1;
		creating_threads(philo, m->nb);
		supervisor(philo, m);
	}
	else
	{
		printf("Error in arguments \n");
		return (0);
	}
}
