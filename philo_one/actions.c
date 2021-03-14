/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:23:41 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/14 14:51:34 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	philo_death(t_philo *philo)
{
	printf("%ld: philo #%d died\n", get_time(), philo->number);
	exit(0);
}

void	*philo_sleep_n_think(void *args)
{
	t_philo	*philo;
	long	cur_time;

	philo = (t_philo *)args;
	cur_time = get_time();
	printf("%ld: philo #%d is sleeping\n", cur_time, philo->number);
	if ((cur_time + philo->args->sleep_time) >
			(philo->last_meal + philo->args->die_time))
	{
		usleep((philo->args->die_time - (cur_time - philo->last_meal)) * 1000);
		philo_death(philo);
	}
	else
		usleep(philo->args->sleep_time * 1000);
	cur_time = get_time();
	printf("%ld: philo #%d is thinking\n", cur_time, philo->number);
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
	printf("%ld: philo #%d has taken a fork\n",
		get_time(), philo->number);
	pthread_mutex_lock(&(philo->right_fork->mtx));
	printf("%ld: philo #%d has taken a fork\n",
		get_time(), philo->number);
	cur_time = get_time();
	philo->last_meal = cur_time;
	printf("%ld: philo #%d is eating\n", cur_time, philo->number);
	usleep(philo->args->eat_time * 1000);
	pthread_mutex_unlock(&(philo->left_fork->mtx));
	pthread_mutex_unlock(&(philo->right_fork->mtx));
	philo->left_fork->enable = 1;
	philo->right_fork->enable = 1;
	philo->cntrl->meals++;
	philo_sleep_n_think(philo);
}
