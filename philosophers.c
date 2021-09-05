#include "philosophers.h"

unsigned long long    get_time(void)
{
    unsigned long long    mili_sec;
    struct timeval        current_time;

    gettimeofday(&current_time, NULL);
    mili_sec = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    
    return (mili_sec);
}
void write_message( unsigned long long time,struct philo *philo, int id)
{
    pthread_mutex_lock(&philo->mutexx->write_mutex);
    if (id == 0)
        printf("%llu Philosofer nb %d is thinking \n",time,philo->id);
    else if(id == 1)
    {
        printf("%llu Philosofer nb %d has taken left fork %d \n",time,philo->id,philo->left_fork);
        printf("%llu Philosofer nb %d has taken right fork %d \n",time,philo->id,philo->right_fork);
    }
    else if (id == 2)
        printf("%llu Philosofer nb %d is sleeping \n",time,philo->id);
    else if (id == 3)
    {
        printf("%llu it was %d who died his last meal was %llu\n",get_time() - current_time, philo->id, philo->last_meal - current_time);
        exit(0);
    }
    pthread_mutex_unlock(&philo->mutexx->write_mutex);
    
}

void        x_usleep(unsigned long long    time)
{
    unsigned long long        r;
    unsigned long long        mic;

    mic = get_time();
    r = time - 60;
    usleep(r * 1000);
    while ((get_time() - mic) < (time))
    {
    }
}

void long_farwell(int t)
{
    unsigned long long    start;
    unsigned long long    time_diff;
    
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

void my_sleep(unsigned long long time)
{
    unsigned long long end = get_time() + time;   
    while (get_time() < end); 
}
void sleep_x(unsigned long long time, ph *philo)
{
    usleep(time * 1000 - 14000);
    while ((get_time() - philo->last_meal)
        < (unsigned long long)60);
}
void thinking(ph *philo)
{
    unsigned long long time = get_time() - current_time;
    write_message(time, philo, 0); 
    
}
void eat(ph *philo)
{
    pthread_mutex_lock(&philo->mutexx->forks[philo->left_fork]);
    pthread_mutex_lock(&philo->mutexx->forks[philo->right_fork]);

    write_message(get_time() - current_time, philo, 1);
    long_farwell(60 * 1000);
    philo->last_meal = get_time();

    pthread_mutex_unlock(&philo->mutexx->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->mutexx->forks[philo->right_fork]);
}

void sleeping(ph *philo)
{   
    unsigned long long time = get_time() - current_time;
    write_message(time, philo, 2);
    long_farwell(60 * 1000);
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
    int j = 0;
    int nb = ft_atoi(argv[1]);
    unsigned long long time;
    struct philo *philo = malloc(sizeof(ph) * ft_atoi(argv[1]));

    m = malloc(sizeof(mutexes));
   //printf("a\n");
    m->forks = malloc(sizeof(pthread_mutex_t) * nb); 
    m->philo = philo;
   //printf("b\n");
    //exit(0);
    while (i < nb)
    {
        philo[i].id = i + 1;
        philo[i].right_fork = (i + 1) % nb;
        philo[i].left_fork = i;
        philo[i].mutexx = m;
        pthread_mutex_init(&philo->mutexx->forks[i], NULL);
        philo[i].last_meal = get_time();
        i++;
    }
    pthread_mutex_init(&m->write_mutex , NULL);
    i = 0;
    current_time = get_time();
    while (i < nb)
    {
        pthread_t  p1;
        // philo[i].last_meal = get_time();
        pthread_create(&p1, NULL, &routine, &philo[i]);
        i += 2;
    }
    usleep(1000);

    i = 1;
    while (i < nb)
    {
        pthread_t  p1;
        // philo[i].last_meal = get_time();
        pthread_create(&p1, NULL, &routine, &philo[i]);
        i += 2;
    }

    while (1)
    {
        j = 0;
        while (j < nb)
        { 
            //printf("at %llu philosopher nb  %d last meal was at %llu \n", get_time() - current_time, j, philo[j].last_meal - current_time);
            if (get_time() - philo[j].last_meal > (unsigned long long)120)
            {
                write_message(get_time(), &philo[j], 3);
                exit(0);
            }
            j++;
        }
        long_farwell(60 * 1000);
    }
    
    

}

