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

void	init(struct t_philo *philo, struct t_mutexes *m, int nb)
{
	m->forks = malloc(sizeof(pthread_mutex_t) * nb);
	m->philo = philo;
}

void	creating_threads(struct t_philo *philo, int nb)
{
	int			i;
	pthread_t	p1;

	i = 0;
	philo->m->current_time = get_time();
	while (i < nb)
	{
		pthread_create(&p1, NULL, &routine, &philo[i]);
		usleep(100);
		i++;
	}
}

int	check_lastarg(int *flag, t_mutexes *m, struct t_philo *philo, int j)
{
	if (m->nb_meals != -1)
	{
		if (philo[j].nb_meals >= m->nb_meals)
			*flag += 1;
		if (*flag >= m->nb)
		{
			w_msg(get_time() - philo->m->current_time, philo, 4);
			philo->m->flag = 0;
			return (0);
		}
	}
	return (1);
}

void	philo_died(struct t_philo *philo, int j)
{
	pthread_mutex_lock(&philo[j].eat_mutex);
	w_msg(get_time() - philo[j].m->current_time, &philo[j], 3);
	pthread_mutex_unlock(&philo[j].eat_mutex);
	philo->m->flag = 0;
}

void	supervisor(struct t_philo *philo, t_mutexes *m)
{
	long				j;
	int					flag;
	unsigned long long	t;
	unsigned long long	t_die;

	t_die = m->time_todie;
	while (philo->m->flag)
	{
		j = 0;
		flag = 0;
		while (j < philo->m->nb)
		{
			t = get_time();
			if (t - philo[j].last_meal >= t_die && t >= philo[j].last_meal)
			{
				while
				(philo[j].is_eating == 1);
				philo_died(philo, j);
				break ;
			}
			if (check_lastarg(&flag, m, philo, j) == 0)
				break ;
			j++;
		}
	}
}
