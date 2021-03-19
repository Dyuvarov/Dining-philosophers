/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:37:03 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/17 13:35:38 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"
#include <string.h>

static void		validate_args(t_args *args, int argc)
{
	if (args->number < 2 || args->die_time < 0 || args->eat_time < 0 \
											|| args->sleep_time < 0)
		ft_error(ARGS_ERR);
	if (argc == 6 && args->eat_num < 0)
		ft_error(ARGS_ERR);
}

static t_args	*initialize_args(char **argv, int argc)
{
	t_args *args;

	if (argc == 6 || argc == 5)
	{
		args = malloc(sizeof(t_args));
		if (!args)
			ft_error(SYSCALL_ERR);
		args->number = ft_atoi(argv[1]);
		args->die_time = ft_atoi(argv[2]);
		args->eat_time = ft_atoi(argv[3]);
		args->sleep_time = ft_atoi(argv[4]);
		args->eat_num = -1;
		if (argc == 6)
			args->eat_num = ft_atoi(argv[5]);
		validate_args(args, argc);
		args->start_t = get_time(0);
		return (args);
	}
	else
		ft_error(ARGS_ERR);
	return (NULL);
}

static void	create_forks(t_philo *philo, int n)
{
	int	i;
	t_philo	*tmp;

	i = 0;
	tmp = philo;
	while (i < n)
	{
		tmp->right_fork = malloc(sizeof(pthread_mutex_t));
		if (!(tmp->right_fork))
			ft_error(SYSCALL_ERR);
		pthread_mutex_init(tmp->right_fork, NULL);
		tmp = tmp->left_philo;
		i++;
	}
	i = 0;
	tmp = philo;
	while (i < n)
	{
		if (i == (n - 1))
			tmp->left_fork = philo->right_fork;
		else
			tmp->left_fork = tmp->left_philo->right_fork;
		tmp = tmp->left_philo;
		i++;
	}
}

static t_philo	*new_philo(int id, t_args *args)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		ft_error(SYSCALL_ERR);
	philo->number = id + 1;
	philo->thread = malloc(sizeof(pthread_t));
	if (!philo->thread)
		ft_error(SYSCALL_ERR);
	philo->args = args;
	philo->activated = 0;
	philo->meal_mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->meal_mtx, NULL);
	return (philo);
}

t_philo			*create_philos(char **argv, int argc)
{
	int		i;
	t_philo	*head;
	t_philo	*tmp;
	t_args	*args;

	args = initialize_args(argv, argc);
	head = new_philo(0, args);
	tmp = head;
	i = 1;
	pthread_mutex_init(&g_output, NULL);
	while (i < args->number)
	{
		tmp->left_philo = new_philo(i, args);
		tmp->left_philo->right_philo = tmp;
		tmp = tmp->left_philo;
		++i;
	}
	tmp->left_philo = head;
	head->right_philo = tmp;
	create_forks(head, head->args->number);
	return (head);
}
