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
    int nb_meals;
    unsigned long long current_time;
    unsigned long long time_todie;
    int nb;
}mutexes;

typedef struct philo{
    int id;
    int left_fork;
    int right_fork;
    unsigned long long time_toeat;
    unsigned long long time_tosleep;
    struct mutexes *mutexx;
    unsigned long long last_meal;
    int nb_meals;
}ph;

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
void *routine(void *test);
void sleeping(ph *philo);
void eat(ph *philo);
void thinking(ph *philo);
unsigned long long    get_time(void);
void write_message( unsigned long long time,struct philo *philo, int id);
void long_farwell(int t);
void get_data(int nb, struct philo *philo, char **argv, mutexes *m);
void creating_threads(struct philo *philo, int nb);
void supervisor(struct philo *philo, mutexes *m);
void init(struct philo *philo, struct mutexes *m, int nb);
size_t ft_strlen(char *str);

#endif