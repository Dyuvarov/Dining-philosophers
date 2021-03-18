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
		return (args);
	}
	else
		ft_error(ARGS_ERR);
	return (NULL);
}

static t_fork	*create_forks(int number)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * number);
	if (!forks)
		ft_error(SYSCALL_ERR);
	i = 0;
	while (i < number)
	{
		forks[i].num = i;
		pthread_mutex_init(&(forks[i].mtx), NULL);
		forks[i].enable = 1;
		++i;
	}
	return (forks);
}

static t_philo	*new_philo(int id, t_args *args, t_fork *forks)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		ft_error(SYSCALL_ERR);
	philo->number = id + 1;
	philo->left_fork = &(forks[id]);
	if (id - 1 >= 0)
		philo->right_fork = &(forks[id - 1]);
	else
		philo->right_fork = &(forks[args->number - 1]);
	philo->thread = malloc(sizeof(pthread_t));
	if (!philo->thread)
		ft_error(SYSCALL_ERR);
	philo->args = args;
	philo->last_meal = get_time();
	pthread_mutex_init(&(philo->mtx), NULL);
	return (philo);
}

t_philo			*create_philos(char **argv, int argc)
{
	int		i;
	t_philo	*head;
	t_philo	*tmp;
	t_args	*args;
	t_fork	*forks;

	args = initialize_args(argv, argc);
	forks = create_forks(args->number);
	head = new_philo(0, args, forks);
	tmp = head;
	i = 1;
	pthread_mutex_init(&g_output, NULL);
	while (i < args->number)
	{
		tmp->left_philo = new_philo(i, args, forks);
		tmp->left_philo->right_philo = tmp;
		tmp = tmp->left_philo;
		++i;
	}
	tmp->left_philo = head;
	head->right_philo = tmp;
	return (head);
}
