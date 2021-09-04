#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct mutexes{
    pthread_mutex_t write_mutex;
    pthread_mutex_t *forks;
    struct philo *philo;
}mutexes;

typedef struct philo{
    int id;
    int left_fork;
    int right_fork;
    struct mutexes *mutexx;
    unsigned long long last_meal;
}ph;

mutexes *m;
unsigned long long current_time;

typedef struct data
{
    int nb_ph;
    int tt_die;
    int tt_sleep;
    int tt_eat;
    int nb_forks;
}data;


int ft_atoi(const char *str);
int	ft_isdigit(int str);

#endif