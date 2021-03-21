/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:36:55 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/21 14:23:31 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "unistd.h"
#include <stdlib.h>

void	cleaner(t_philo *philo, int i)
{
	if (i == (philo->number - 1))
	{
		cleaner(philo->left_philo, i + 1);
		if (i == 0)
		{
			free(philo->args);
			free(philo->cntrl);
		}
		pthread_detach(*(philo->thread));
		pthread_mutex_destroy(philo->meal_mtx);
		pthread_mutex_destroy(philo->left_fork);
		pthread_mutex_destroy(philo->right_fork);
		free(philo);
	}
	else
		return ;
}

void	ft_error(int code, t_philo *philo)
{
	if (code == ARGS_ERR)
		write(2, "ERROR: Wrong options!\n",
			ft_strlen("ERROR: Wrong options!\n"));
	else if (code == SYSCALL_ERR)
		write(2, "ERROR: system call failed!\n",
			ft_strlen("ERROR: system call failed!\n"));
	if (philo)
		cleaner(philo, 0);
	exit(EXIT_FAILURE);
}
