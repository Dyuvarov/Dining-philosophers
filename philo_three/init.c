#include "philo.h"
#include <stdlib.h>

static void		validate_args(t_args *args, int argc)
{
	if (args->number < 2 || args->die_time < 0 || args->eat_time < 0 \
											|| args->sleep_time < 0)
		ft_error(ARGS_ERR, args);
	if (argc == 6 && args->eat_num < 0)
		ft_error(ARGS_ERR, args);
}

static t_philo	*new_philo(int id, t_args *args)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		ft_error(SYSCALL_ERR, args);
	philo->number = id + 1;
	philo->args = args;
	philo->meals = 0;
	philo->last_meal = args->start_t;
	philo->sem_name = ft_itoa(philo->number);
	philo->meal_sem_name = ft_itoa(philo->number + args->number);
	if (!philo->sem_name || !philo->meal_sem_name)
		ft_error(SYSCALL_ERR, args);
	philo->meal_count_sem = init_sem(philo->sem_name, 0);
	philo->meal_sem = init_sem(philo->meal_sem_name, 1);
	return (philo);
}

t_args			*initialize_args(char **argv, int argc)
{
	t_args *args;

	if (argc == 6 || argc == 5)
	{
		args = malloc(sizeof(t_args));
		if (!args)
			ft_error(SYSCALL_ERR, args);
		args->number = ft_atoi(argv[1]);
		args->die_time = ft_atoi(argv[2]);
		args->eat_time = ft_atoi(argv[3]);
		args->sleep_time = ft_atoi(argv[4]);
		args->eat_num = -1;
		if (argc == 6)
			args->eat_num = ft_atoi(argv[5]);
		validate_args(args, argc);
		args->start_t = get_time(0);
		args->forks_sem = init_sem("forks", (args->number / 2));
		args->output_sem = init_sem("output", 1);
		args->finish_sem = init_sem("finish", 0);
		return (args);
	}
	else
		ft_error(ARGS_ERR, NULL);
	return (NULL);
}

t_philo			*create_philos(t_args *args)
{
	int		i;
	t_philo	*head;
	t_philo	*tmp;

	head = new_philo(0, args);
	tmp = head;
	i = 1;
	while (i < args->number)
	{
		tmp->left_philo = new_philo(i, args);
		tmp->left_philo->right_philo = tmp;
		tmp = tmp->left_philo;
		++i;
	}
	tmp->left_philo = head;
	head->right_philo = tmp;
	return (head);
}
