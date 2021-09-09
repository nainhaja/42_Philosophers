/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:54:39 by nainhaja          #+#    #+#             */
/*   Updated: 2021/09/07 16:54:41 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_ph *philo)
{
	unsigned long long	time;

	time = get_time() - philo->m->current_time;
	w_msg(time, philo, 0);
}

void	print_eating(unsigned long long time, struct t_philo *philo)
{
	pthread_mutex_lock(&philo->m->write_mutex);
	printf("%llu %d has taken fork \n", time, philo->id);
	if (philo->m->nb != 1)
	{
		printf("%llu %d has taken fork \n", time, philo->id);
		printf("%llu %d is eating \n", time, philo->id);
	}
	else
		long_farwell(philo->m->time_todie * 1000);
	pthread_mutex_unlock(&philo->m->write_mutex);
}

void	eat(t_ph *philo)
{
	pthread_mutex_lock(&philo->m->forks[philo->left_fork]);
	if (philo->m->nb != 1)
	{
		pthread_mutex_lock(&philo->m->forks[philo->right_fork]);
		philo->is_eating = 1;
	}
	print_eating(get_time() - philo->m->current_time, philo);
	long_farwell(philo->time_toeat * 1000);
	philo->last_meal = get_time();
	philo->is_eating = 0;
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->m->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->m->forks[philo->right_fork]);
}

void	sleeping(t_ph *philo)
{
	unsigned long long	time;

	time = get_time() - philo->m->current_time;
	w_msg(time, philo, 2);
	long_farwell(philo->time_tosleep * 1000);
}

void	*routine(void *test)
{
	struct t_philo	*philo;

	philo = (struct t_philo *)test;
	philo->last_meal = get_time();
	while (philo->m->flag)
	{
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}
