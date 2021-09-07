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
			printf("Error in Arguments \n");
			exit(0);
		}
		i++;
	}
}

void	check_arg(char **argv, int argc, mutexes *m)
{
	if (argc == 6)
		m->nb_meals = ft_atoi(argv[5]);
	else
		m->nb_meals = -1;
	m->time_todie = ft_atoi(argv[2]);
	m->nb = ft_atoi(argv[1]);
	last_check(argv, argc);
}

void	print_error(void)
{
	printf("Missing or too many arguments \n");
	exit(0);
}

int	main(int argc, char **argv)
{
	struct philo	*philo;
	mutexes			*m;

	m = malloc(sizeof(mutexes));
	if (argc == 5 || argc == 6)
	{
		check_arg(argv, argc, m);
		philo = malloc(sizeof(ph) * m->nb);
		init(philo, m, m->nb);
		get_data(m->nb, philo, argv, m);
		creating_threads(philo, m->nb);
		supervisor(philo, m);
	}
	else
		print_error();
}
