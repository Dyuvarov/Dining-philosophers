/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:06:59 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/23 14:07:47 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	*philo_controll(void *args)
{
	t_philo	*philo;
	t_args	*arg;

	philo = (t_philo *)args;
	arg = philo->args;
	while (1)
	{
		sem_wait(philo->meal_sem);
		if ((get_time(arg->start_t) - philo->last_meal) >= (arg->die_time + 9))
			philo_death(philo);
		sem_post(philo->meal_sem);
		if (arg->eat_num >= 0 && (philo->meals >= arg->eat_num))
			sem_post(philo->meal_count_sem);
	}
	return (NULL);
}

void	*meal_count_controll(void *args)
{
	t_philo	*head_philo;
	t_philo	*tmp;
	int		i;

	i = 0;
	head_philo = (t_philo *)args;
	tmp = head_philo;
	while (i < head_philo->args->number)
	{
		sem_wait(tmp->meal_count_sem);
		tmp = tmp->left_philo;
		++i;
	}
	sem_wait(head_philo->args->output_sem);
	write(1, "ALL PHILOSOPHERS ATE ENOUGH\n",
		ft_strlen("ALL PHILOSOPHERS ATE ENOUGH\n"));
	sem_post(head_philo->args->output_sem);
	sem_post(head_philo->args->finish_sem);
	return (NULL);
}
