/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:36:23 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/23 13:55:18 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include "unistd.h"

t_controller	*create_meal_control(t_philo **head_philo)
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

static void		check_death(t_philo *philo, t_args *arg)
{
	sem_wait(philo->meal_sem);
	if ((get_time(arg->start_t) - philo->last_meal) >= (arg->die_time + 9))
		philo_death(philo);
	sem_post(philo->meal_sem);
}

void			*meals_controll(void *args)
{
	t_controller	*ctrl;
	int				flag;
	int				i;
	t_args			*arg;

	ctrl = (t_controller *)args;
	arg = ctrl[0].philo->args;
	while (1)
	{
		i = 0;
		flag = 1;
		while (ctrl[i].philo && ctrl[i].philo->activated)
		{
			check_death(ctrl[i].philo, arg);
			if (arg->eat_num >= 0 && (ctrl[i].meals < arg->eat_num))
				flag = 0;
			++i;
		}
		if (arg->eat_num >= 0 && flag)
			break ;
	}
	ate_enough_msg(ctrl[0].philo);
	exit(EXIT_SUCCESS);
}

void			start_controller(t_philo *head_philo)
{
	pthread_t		meal_ctrl_thread;
	t_controller	*meal_control;

	meal_control = create_meal_control(&head_philo);
	pthread_create(&meal_ctrl_thread, NULL, meals_controll, meal_control);
	pthread_join(meal_ctrl_thread, NULL);
	pthread_detach(meal_ctrl_thread);
}
