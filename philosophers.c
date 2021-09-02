#include "philosophers.h"

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
    pthread_mutex_lock(&mutex->write_mutex);
    if (id == 0)
        printf("%llu Philosofer nb %d is thinking \n",time,philo->id);
    else if(id == 1)
    {
        printf("%llu Philosofer nb %d has taken left fork %d \n",time,philo->id,philo->left_fork);
        printf("%llu Philosofer nb %d has taken right fork %d \n",time,philo->id,philo->right_fork);
    }
    else if (id == 2)
        printf("%llu Philosofer nb %d is sleeping \n",time,philo->id);
    pthread_mutex_unlock(&mutex->write_mutex);
    
}

void my_sleep(unsigned long long time)
{
    unsigned long long end = get_time() + time;   
    while (get_time() < end); 
}
void thinking(ph *philo)
{
    unsigned long long time = get_time() - current_time;
    write_message(m, time, philo, 0); 
    
}
void eat(ph *philo)
{
    unsigned long long time;
    if (get_time() - philo->last_meal > (unsigned long long)60)
    {
        printf("Similation ended \n");
        exit(0);
    }
    pthread_mutex_lock(&m->forks[philo->left_fork]);
    pthread_mutex_lock(&m->forks[philo->right_fork]);
    
    time = get_time() - current_time;
    write_message(m, time, philo, 1);
    my_sleep(60);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&m->forks[philo->left_fork]);
    pthread_mutex_unlock(&m->forks[philo->right_fork]);
    
    

}

void sleeping(ph *philo)
{   
    unsigned long long time = get_time() - current_time;
    write_message(m, time, philo, 2);
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
    m = malloc(sizeof(mutexes));
   //printf("a\n");
    m->forks = malloc(sizeof(pthread_mutex_t) * nb); 
   //printf("b\n");
    //exit(0);
    while (i < nb)
    {
        philo[i].id = i + 1;
        philo[i].right_fork = (i + 1) % nb;
        philo[i].left_fork = i;
        pthread_mutex_init(&m->forks[i], NULL);
        philo[i].last_meal = get_time();
        i++;
    }
     
    pthread_mutex_init(&m->write_mutex , NULL);
    i = 0;
    current_time = get_time();
        while (i < nb)
        {
            pthread_t  p1;
            pthread_create(&p1, NULL, &routine, &philo[i]);
            i++;
        }
    while (1)
    {
        /* code */
    }
    
    

}

