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
	int		i;
	t_philo *tmp;

	show_msg("%ld: philo #%d died\n", get_time(), philo->number);
	i = 0;
	tmp = philo;
	while(i < philo->args->number)
	{
		pthread_detach(*(philo->thread));
		tmp = tmp->left_philo;
		++i;
	}
	unlink_sems();
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
	sem_wait(g_forks);
	show_msg("%ld: philo #%d has taken a fork\n",
			 get_time(), philo->number);
	show_msg("%ld: philo #%d has taken a fork\n",
		get_time(), philo->number);
	cur_time = get_time();
	philo->last_meal = cur_time;
	show_msg("%ld: philo #%d is eating\n", cur_time, philo->number);
	usleep(philo->args->eat_time * 1000);
	sem_post(g_forks);
	philo->cntrl->meals++;
	philo_sleep_n_think(philo);
}
