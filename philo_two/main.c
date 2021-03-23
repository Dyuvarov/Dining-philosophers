/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:35:55 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/23 13:43:29 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void	wait_threads_finish(t_philo *head_philo)
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

static void	*philo_start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->activated = 1;
	while (1)
		eat(&philo);
	return (NULL);
}

int			main(int argc, char **argv)
{
	t_philo			*head_philo;
	t_philo			*philo;
	int				i;
	t_args			*args;

	args = initialize_args(argv, argc);
	unlink_sems(args);
	head_philo = create_philos(args);
	philo = head_philo;
	i = 0;
	while (i < head_philo->args->number)
	{
		pthread_create(philo->thread, NULL, philo_start, philo);
		philo = philo->left_philo;
		++i;
	}
	start_controller(head_philo);
	wait_threads_finish(head_philo);
	return (EXIT_SUCCESS);
}
