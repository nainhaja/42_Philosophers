/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:47:39 by nainhaja          #+#    #+#             */
/*   Updated: 2021/09/07 16:47:41 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(struct philo *philo, struct mutexes *m, int nb)
{
	m->forks = malloc(sizeof(pthread_mutex_t) * nb);
	m->philo = philo;
}

void	creating_threads(struct philo *philo, int nb)
{
	int			i;
	pthread_t	p1;

	i = 0;
	philo->mutexx->current_time = get_time();
	while (i < nb)
	{
		pthread_create(&p1, NULL, &routine, &philo[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < nb)
	{
		pthread_create(&p1, NULL, &routine, &philo[i]);
		i += 2;
	}
}

void	check_lastarg(int *flag, mutexes *m, struct philo *philo, int j)
{
	if (m->nb_meals != -1)
	{
		if (philo[j].nb_meals >= m->nb_meals)
			*flag += 1;
		if (*flag >= m->nb)
		{
			write_message(get_time() - m->current_time, philo, 4);
			exit(0);
		}
	}
}

void	supervisor(struct philo *philo, mutexes *m)
{
	int	j;
	int	flag;

	while (1)
	{
		j = 0;
		flag = 0;
		while (j < m->nb)
		{
			if (get_time() - philo[j].last_meal > m->time_todie)
			{
				write_message(get_time() - m->current_time, &philo[j], 3);
				exit(0);
			}
			check_lastarg(&flag, m, philo, j);
			j++;
		}
	}
}
