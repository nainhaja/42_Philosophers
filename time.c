/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:48:36 by nainhaja          #+#    #+#             */
/*   Updated: 2021/09/07 18:48:37 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	get_time(void)
{
	unsigned long long	mili_sec;
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	mili_sec = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (mili_sec);
}

void	w_msg(unsigned long long time, struct t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->m->write_mutex);
	if (id == 0)
		printf("%llu %d is thinking \n", time, philo->id);
	else if (id == 2)
		printf("%llu %d is sleeping \n", time, philo->id);
	else if (id == 3)
	{
		printf("%llu %d died \n", time, philo->id);
		return ;
	}
	else if (id == 4)
		return ;
	pthread_mutex_unlock(&philo->m->write_mutex);
}

void	long_farwell(int t)
{
	long long			start;
	unsigned long long	time_diff;

	start = get_time() * 1000;
	while (1)
	{
		time_diff = t - (get_time() * 1000 - start);
		if (time_diff < 50)
		{
			usleep(time_diff);
			break ;
		}
		if (time_diff > (unsigned long long)t)
			break ;
		usleep(50);
	}
}

void	data(int nb, struct t_philo *philo, char **argv, t_mutexes *m)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = (i + 1) % nb;
		philo[i].left_fork = i;
		philo[i].m = m;
		philo[i].time_toeat = ft_atoi(argv[3]);
		philo[i].time_tosleep = ft_atoi(argv[4]);
		philo[i].nb_meals = 0;
		pthread_mutex_init(&philo[i].eat_mutex, NULL);
		pthread_mutex_init(&philo->m->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&m->write_mutex, NULL);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
