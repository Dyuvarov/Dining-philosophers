#include "philo.h"
#include <stdlib.h>

static void		validate_args(t_args *args, int argc)
{
	if (args->number < 2 || args->die_time < 0 || args->eat_time < 0 \
											|| args->sleep_time < 0)
		ft_error(ARGS_ERR);
	if (argc == 6 && args->eat_num < 0)
		ft_error(ARGS_ERR);
}

static t_philo	*new_philo(int id, t_args *args)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		ft_error(SYSCALL_ERR);
	philo->number = id + 1;
	philo->args = args;
	return (philo);
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

t_philo			*create_philos(char **argv, int argc)
{
	int		i;
	t_philo	*head;
	t_philo	*tmp;
	t_args	*args;
	long 	cur_time;

	args = initialize_args(argv, argc);
	head = new_philo(0, args);
	tmp = head;
	i = 1;
	cur_time = get_time();
	while (i < args->number)
	{
		tmp->left_philo = new_philo(i, args);
		tmp->left_philo->right_philo = tmp;
		tmp->last_meal = cur_time;
		tmp = tmp->left_philo;
		++i;
	}
	tmp->left_philo = head;
	head->right_philo = tmp;
	tmp->last_meal = cur_time;
	return (head);
}