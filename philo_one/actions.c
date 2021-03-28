#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ate_enough_msh(t_philo *philo)
{
	pthread_mutex_lock(philo->args->output);
	write(1, "ALL PHILOSOPHERS ATE ENOUGH\n",
		ft_strlen("ALL PHILOSOPHERS ATE ENOUGH\n"));
	pthread_mutex_unlock(philo->args->output);
	cleaner(philo, 0);
}

void	show_msg(const char *str, long time, t_philo *philo)
{
	pthread_mutex_lock(philo->args->output);
	printf(str, time, philo->number);
	pthread_mutex_unlock(philo->args->output);
}

void	philo_death(t_philo *philo)
{
	t_args *arg;

	arg = philo->args;
	show_msg("%ld: philo #%d died\n", get_time(arg->start_t), philo);
	exit(0);
}

void	*philo_sleep_n_think(void *args)
{
	t_philo	*philo;
	long	cur_time;
	t_args	*arg;

	philo = (t_philo *)args;
	arg = philo->args;
	cur_time = get_time(arg->start_t);
	show_msg("%ld: philo #%d is sleeping\n", cur_time, philo);
	usleep(arg->sleep_time * 1000);
	cur_time = get_time(arg->start_t);
	show_msg("%ld: philo #%d is thinking\n", cur_time, philo);
	return (NULL);
}

void	eat(t_philo **ph)
{
	t_philo	*philo;
	long	cur_time;
	t_args	*arg;

	philo = *ph;
	arg = philo->args;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->meal_mtx);
	cur_time = get_time(arg->start_t);
	philo->last_meal = cur_time;
	pthread_mutex_unlock(philo->meal_mtx);
	show_msg("%ld: philo #%d has taken a fork\n",
		cur_time, philo);
	show_msg("%ld: philo #%d has taken a fork\n",
		cur_time, philo);
	show_msg("%ld: philo #%d is eating\n", cur_time, philo);
	philo->cntrl->meals++;
	usleep(arg->eat_time * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo_sleep_n_think(philo);
}
