#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

static void	*philo_start(void *args)
{
	t_philo			*philo;
	pthread_t		meal_ctrl_thread;

	philo = (t_philo *)args;
	pthread_create(&meal_ctrl_thread, NULL, philo_controll, args);
	while (1)
	{
		eat(&philo);
		philo_sleep_n_think(philo);
	}
	pthread_detach(meal_ctrl_thread);
}

void		create_procceses(t_philo **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		arr[i]->pid = fork();
		if (arr[i]->pid < 0)
			ft_error(SYSCALL_ERR, arr[i]->args);
		else if (arr[i]->pid == 0)
		{
			philo_start(arr[i]);
			exit(EXIT_SUCCESS);
		}
		++i;
	}
}

t_philo		**get_philo_arr(t_philo *head_philo)
{
	t_philo	**arr;
	t_philo	*tmp;
	int		i;

	arr = malloc(sizeof(t_philo *) * (head_philo->args->number + 1));
	if (!arr)
		ft_error(SYSCALL_ERR, head_philo->args);
	i = 0;
	tmp = head_philo;
	while (i < head_philo->args->number)
	{
		arr[i] = tmp;
		tmp = tmp->left_philo;
		++i;
	}
	arr[i] = NULL;
	return (arr);
}

int			main(int argc, char **argv)
{
	t_philo			*head_philo;
	t_philo			**philo_arr;
	pthread_t		meal_count_controller;
	int				i;
	t_args			*args;

	args = initialize_args(argv, argc);
	unlink_sems(args);
	head_philo = create_philos(args);
	philo_arr = get_philo_arr(head_philo);
	pthread_create(&meal_count_controller, NULL,
		meal_count_controll, head_philo);
	create_procceses(philo_arr);
	sem_wait(args->finish_sem);
	sem_wait(args->output_sem);
	i = 0;
	while (philo_arr[i])
	{
		kill(philo_arr[i]->pid, SIGQUIT);
		++i;
	}
	pthread_detach(meal_count_controller);
	unlink_sems(args);
	return (0);
}
