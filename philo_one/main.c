/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:37:09 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/14 14:50:54 by ugreyiro         ###   ########.fr       */
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
	philo->last_meal = get_time();
	while (1)
	{
		if (philo->left_fork->enable && philo->right_fork->enable)
			eat(&philo);
		else if ((get_time() - philo->last_meal) > philo->args->die_time)
			philo_death(philo);
	}
}

static t_controller	*create_meal_control(t_philo **head_philo)
{
	int				i;
	t_controller	*ctrl;
	t_philo			*ph_tmp;

	ctrl = malloc(sizeof(t_controller) * ((*head_philo)->args->number + 1));
	if (!ctrl)
		ft_error(SYSCALL_ERR);
	ph_tmp = *head_philo;
	i = 0;
	while (i < ph_tmp->args->number)
	{
		ctrl[i].philo = ph_tmp;
		ctrl[i].meals = 0;
		ph_tmp->cntrl = &ctrl[i];
		ph_tmp = ph_tmp->left_philo;
		++i;
	}
	ctrl[i].philo = NULL;
	return (ctrl);
}

static void			*meals_controll(void *args)
{
	t_controller	*ctrl;
	int				flag;
	int				i;

	ctrl = (t_controller *)args;
	while (1)
	{
		i = 0;
		flag = 1;
		while (ctrl[i].philo)
		{
			if (ctrl[i].meals < ctrl[i].philo->args->eat_num)
				flag = 0;
			++i;
		}
		if (flag)
			break ;
	}
	exit(0);
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
	if (head_philo->args->eat_num >= 0)
	{
		pthread_create(&meal_ctrl_thread, NULL, meals_controll, meal_control);
		pthread_join(meal_ctrl_thread, NULL);
		pthread_detach(meal_ctrl_thread);
	}
	wait_threads_finish(head_philo);
	return (0);
}
