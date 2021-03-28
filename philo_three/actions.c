#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

void	philo_death(t_philo *philo)
{
	show_msg("%ld: philo #%d died\n", get_time(philo->args->start_t), philo);
	sem_post(philo->args->finish_sem);
	exit(EXIT_SUCCESS);
}

void	*philo_sleep_n_think(void *args)
{
	t_philo	*philo;
	long	cur_time;

	philo = (t_philo *)args;
	cur_time = get_time(philo->args->start_t);
	show_msg("%ld: philo #%d is sleeping\n", cur_time, philo);
	usleep(philo->args->sleep_time * 1000);
	cur_time = get_time(philo->args->start_t);
	show_msg("%ld: philo #%d is thinking\n", cur_time, philo);
	return (NULL);
}

void	eat(t_philo **ph)
{
	t_philo	*philo;
	long	cur_time;

	philo = *ph;
	sem_wait(philo->args->forks_sem);
	sem_wait(philo->meal_sem);
	cur_time = get_time(philo->args->start_t);
	philo->last_meal = cur_time;
	sem_post(philo->meal_sem);
	show_msg("%ld: philo #%d has taken a fork\n",
			cur_time, philo);
	show_msg("%ld: philo #%d has taken a fork\n",
			cur_time, philo);
	show_msg("%ld: philo #%d is eating\n", cur_time, philo);
	usleep(philo->args->eat_time * 1000);
	sem_post(philo->args->forks_sem);
	philo->meals++;
}
