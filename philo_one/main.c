/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:37:09 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/23 13:05:38 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"
#include <stdlib.h>

static void			*philo_start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->last_meal = get_time(philo->args->start_t);
	philo->activated = 1;
	while (1)
	{
		eat(&philo);
	}
	return (NULL);
}

static void			wait_threads_finish(t_philo *head_philo)
{
	t_philo	*philo;
	int		i;

	philo = head_philo;
	i = 0;
	while (i < head_philo->args->number)
	{
		pthread_join(*(philo->thread), NULL);
		pthread_detach(*(philo->thread));
		philo = philo->left_philo;
		++i;
	}
}

int					main(int argc, char **argv)
{
	t_philo			*head_philo;
	t_philo			*philo;
	pthread_t		meal_ctrl_thread;
	t_controller	*meal_control;
	int				i;

	head_philo = create_philos(argv, argc);
	meal_control = create_meal_control(&head_philo);
	philo = head_philo;
	i = 0;
	while (i < head_philo->args->number)
	{
		pthread_create(philo->thread, NULL, philo_start, philo);
		philo = philo->left_philo;
		++i;
	}
	pthread_create(&meal_ctrl_thread, NULL, meals_controll, meal_control);
	pthread_join(meal_ctrl_thread, NULL);
	pthread_detach(meal_ctrl_thread);
	wait_threads_finish(head_philo);
	return (0);
}
