/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:53:00 by nainhaja          #+#    #+#             */
/*   Updated: 2021/09/08 13:53:01 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct t_mutexes{
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		*forks;
	struct t_philo		*philo;
	int					nb_meals;
	unsigned long long	current_time;
	unsigned long long	time_todie;
	int					nb;
	int					flag;
}t_mutexes;

typedef struct t_philo{
	int					id;
	int					left_fork;
	int					right_fork;
	unsigned long long	time_toeat;
	unsigned long long	time_tosleep;
	struct t_mutexes	*m;
	unsigned long long	last_meal;
	int					nb_meals;
	pthread_mutex_t		eat_mutex;
	int					is_eating;
}t_ph;

long					ft_atoi(const char *str);
int						ft_isdigit(int str);
void					*routine(void *test);
void					sleeping(t_ph *philo);
void					eat(t_ph *philo);
void					thinking(t_ph *philo);
unsigned long long		get_time(void);
void					w_msg(unsigned long long t, struct t_philo *ph, int id);
void					long_farwell(int t);
void					data(int n, struct t_philo *p, char **a, t_mutexes *m);
void					creating_threads(struct t_philo *philo, int nb);
void					supervisor(struct t_philo *philo, t_mutexes *m);
void					init(struct t_philo *p, struct t_mutexes *m, int nb);
size_t					ft_strlen(char *str);
void					print_eating(unsigned long long t, struct t_philo *p);

#endif
