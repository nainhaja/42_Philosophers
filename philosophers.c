#include "philosophers.h"

typedef struct mutexes{
    pthread_mutex_t write_mutex;
    pthread_mutex_t *forks;

}mutexes;

typedef struct philo{
    int id;
    int left_fork;
    int right_fork;
    mutexes *mutexx;
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

mutexes mutexs;
// pthread_mutex_t *forks;

unsigned long long    get_time(void)
{
    unsigned long long    mili_sec;
    struct timeval        current_time;

    gettimeofday(&current_time, NULL);
    mili_sec = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    return (mili_sec);
}
void write_message(mutexes *mutex, unsigned long long time,ph *philo, int id)
{
    pthread_mutex_lock(&mutexs.write_mutex);
    if (id == 0)
        printf("%llu Philosofer nb %d is thinking \n",time,philo->id);
    else if(id == 1)
    {
        printf("%llu Philosofer nb %d has taken left fork %d \n",time,philo->id,philo->left_fork);
        printf("%llu Philosofer nb %d has taken right fork %d \n",time,philo->id,philo->right_fork);
    }
    else if (id == 2)
        printf("%llu Philosofer nb %d is sleeping \n",time,philo->id);
    pthread_mutex_unlock(&mutexs.write_mutex);
}

void my_sleep(long time)
{
    const long end = get_time() + time;   
    while (get_time() < end); 
}
void thinking(ph *philo)
{
    
    unsigned long long time = get_time() - current_time;
    write_message(philo->mutexx, time, philo, 0); 
    
}
void eat(ph *philo)
{
    unsigned long long time;
    
    pthread_mutex_lock(&mutexs.forks[philo->left_fork]);
    pthread_mutex_lock(&mutexs.forks[philo->right_fork]);
    
    time = get_time() - current_time;
    write_message(philo->mutexx, time, philo, 1);
    my_sleep(60);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&mutexs.forks[philo->left_fork]);
    pthread_mutex_unlock(&mutexs.forks[philo->right_fork]);
    
    

}



void sleeping(ph *philo)
{   
    unsigned long long time = get_time() - current_time;
    write_message(philo->mutexx, time, philo, 2);
    my_sleep(60);
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
        //philo[i] = get_time();
        i++;
    }
    mutexs.forks = malloc(sizeof(pthread_mutex_t) * nb);
    
    //printf("%llu time ",get_time());
    i = 0;
    //usleep(60 * 1000);
    //printf("%llu\n",get_time() - time);
    current_time = get_time();
    // while (1)
    // {
        while (i < nb)
        {
            pthread_t  p1;
             philo[i].last_meal = get_time();

            pthread_mutex_init(&mutexs.forks[i], NULL);
            pthread_mutex_init(&mutexs.write_mutex , NULL);
            pthread_create(&p1, NULL, &routine, &philo[i]);
        
        // pthread_join(p1, NULL);
            i++;
        }
    while (1)
    {
        /* code */
    }
    
    

}

