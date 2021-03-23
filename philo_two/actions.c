/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:23:41 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/23 13:28:32 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void	philo_death(t_philo *philo)
{
	int		i;
	t_philo *tmp;

	show_msg("%ld: philo #%d died\n", get_time(philo->args->start_t), philo);
	i = 0;
	tmp = philo;
	while (i < philo->args->number)
	{
		pthread_detach(*(philo->thread));
		tmp = tmp->left_philo;
		++i;
	}
	unlink_sems(philo->args);
	exit(EXIT_SUCCESS);
}

void	philo_sleep_n_think(t_philo *philo)
{
	long	cur_time;
	t_args	*arg;

	arg = philo->args;
	cur_time = get_time(arg->start_t);
	show_msg("%ld: philo #%d is sleeping\n", cur_time, philo);
	usleep(arg->sleep_time * 1000);
	cur_time = get_time(arg->start_t);
	show_msg("%ld: philo #%d is thinking\n", cur_time, philo);
}

void	eat(t_philo **ph)
{
	t_philo	*philo;
	long	cur_time;
	t_args	*arg;

	philo = *ph;
	arg = philo->args;
	sem_wait(arg->forks_sem);
	sem_wait(philo->meal_sem);
	cur_time = get_time(arg->start_t);
	philo->last_meal = cur_time;
	sem_post(philo->meal_sem);
	show_msg("%ld: philo #%d has taken a fork\n",
			cur_time, philo);
	show_msg("%ld: philo #%d has taken a fork\n",
			cur_time, philo);
	show_msg("%ld: philo #%d is eating\n", cur_time, philo);
	philo->cntrl->meals++;
	usleep(arg->eat_time * 1000);
	sem_post(arg->forks_sem);
	philo_sleep_n_think(philo);
}
