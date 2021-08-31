#include "philosophers.h"

typedef struct philo{
    int id;
    int left_fork;
    int right_fork;
    pthread_mutex_t write_mutex;
    unsigned long long last_meal;
}ph;
unsigned long long current_time;
typedef struct data
{
    int nb_ph;
    int tt_die;
    int tt_sleep;
    int tt_eat;
    int nb_forks;
}data;

pthread_mutex_t *forks;

unsigned long long    get_time(void)
{
    unsigned long long    mili_sec;
    struct timeval        current_time;

    gettimeofday(&current_time, NULL);
    mili_sec = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    return (mili_sec);
}
void eat(ph *philo)
{

    
    pthread_mutex_lock(&forks[philo->left_fork]);
    pthread_mutex_lock(&forks[philo->right_fork]);
    pthread_mutex_lock(&philo->write_mutex);
    unsigned long long time = get_time() - current_time;
    printf("%llu Philo nb %d taken left fork %d\n",time,philo->id, philo->left_fork);
    printf("%llu Philo nb %d taken right fork %d\n",time,philo->id, philo->right_fork);
    usleep(60 * 1000 - 14000);
    while ((get_time() - philo->last_meal)
        < (unsigned long long)60);
    pthread_mutex_unlock(&forks[philo->left_fork]);
    pthread_mutex_unlock(&forks[philo->right_fork]);

    philo->last_meal = get_time();

}

void thinking(ph *philo)
{
     unsigned long long time = get_time() - current_time;
    pthread_mutex_unlock(&philo->write_mutex);
   
    printf("%llu Philosofer %d is thinking \n",time,philo->id);
}

void sleeping(ph *philo)
{
    unsigned long long time = get_time() - current_time;
    printf("%llu Philosofer %d is sleeping \n",time,philo->id);
    usleep(60 * 1000 - 14000);
    while ((get_time() - philo->last_meal)
        < (unsigned long long)60);
}

void *routine(void *test)
{
    ph *philo = (ph*) test;
    while (1)
    {
        thinking(philo);
        eat(philo);
        sleeping(philo);
    }
    
    return 0;
}
int main(int argc, char **argv)
{
    int i = 0;
    int nb = ft_atoi(argv[1]);
    unsigned long long time;
    ph *philo = malloc(sizeof(ph) * ft_atoi(argv[1]));
    
    while (i < nb)
    {
        philo[i].id = i + 1;
        philo[i].right_fork = (i + 1) % nb;
        philo[i].left_fork = i;
        philo[i].last_meal = get_time();
        i++;
    }
    forks = malloc(sizeof(pthread_mutex_t) * nb);
    
    //printf("%llu time ",get_time());
    i = 0;
    //usleep(60 * 1000);
    //printf("%llu\n",get_time() - time);
    current_time = get_time();
    while (1)
    {
        while (i < nb)
        {
            pthread_t  p1;
            
            pthread_mutex_init(&forks[i], NULL);
            pthread_mutex_init(&philo[i].write_mutex, NULL);
            pthread_create(&p1, NULL, &routine, &philo[i]);
        
        // pthread_join(p1, NULL);
            i++;
        }
    }
    

}

