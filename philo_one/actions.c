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

void 	show_msg(const char *str, long time, int philo_number)
{
	pthread_mutex_lock(&g_output);
	printf(str, time, philo_number);
	pthread_mutex_unlock(&g_output);
}

void	philo_death(t_philo *philo)
{
	show_msg("%ld: philo #%d died\n", get_time(), philo->number);
	exit(0);
}

void	*philo_sleep_n_think(void *args)
{
	t_philo	*philo;
	long	cur_time;

	philo = (t_philo *)args;
	cur_time = get_time();
	show_msg("%ld: philo #%d is sleeping\n", cur_time, philo->number);
	usleep(philo->args->sleep_time * 1000);
	cur_time = get_time();
	show_msg("%ld: philo #%d is thinking\n", cur_time, philo->number);
	return (NULL);
}

void	eat(t_philo **ph)
{
	t_philo	*philo;
	long	cur_time;

	philo = *ph;
	philo->left_fork->enable = 0;
	philo->right_fork->enable = 0;
	pthread_mutex_lock(&(philo->left_fork->mtx));
	show_msg("%ld: philo #%d has taken a fork\n",
		get_time(), philo->number);
	pthread_mutex_lock(&(philo->right_fork->mtx));
	show_msg("%ld: philo #%d has taken a fork\n",
		get_time(), philo->number);
	cur_time = get_time();
	philo->last_meal = cur_time;
	show_msg("%ld: philo #%d is eating\n", cur_time, philo->number);
	usleep(philo->args->eat_time * 1000);
	philo->left_fork->enable = 1;
	philo->right_fork->enable = 1;
	pthread_mutex_unlock(&(philo->left_fork->mtx));
	pthread_mutex_unlock(&(philo->right_fork->mtx));
	philo->cntrl->meals++;
	philo_sleep_n_think(philo);
}
