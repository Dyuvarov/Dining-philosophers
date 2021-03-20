/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:23:41 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/17 13:12:30 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void 	show_msg(const char *str, long time, t_philo *philo)
{
	pthread_mutex_lock(philo->args->output);
	printf(str, time, philo->number);
	pthread_mutex_unlock(philo->args->output);
}

void	philo_death(t_philo *philo)
{
	show_msg("%ld: philo #%d died\n", get_time(philo->args->start_t),
		       	philo);
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
	philo->cntrl->meals++;
	pthread_mutex_unlock(philo->meal_mtx);
	show_msg("%ld: philo #%d has taken a fork\n",
		cur_time, philo);
	show_msg("%ld: philo #%d has taken a fork\n",
		cur_time, philo);
	show_msg("%ld: philo #%d is eating\n", cur_time, philo);
	usleep(arg->eat_time * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo_sleep_n_think(philo);
}
