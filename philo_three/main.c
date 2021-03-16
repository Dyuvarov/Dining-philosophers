#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

void	*controll(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while(1)
	{
		if ((get_time() - philo->last_meal) > philo->args->die_time)
			philo_death(philo);
	}
	return (NULL);
}

static void			*philo_start(void *args)
{
	t_philo			*philo;
	pthread_t		meal_ctrl_thread;

	philo = (t_philo *)args;
	pthread_create(&meal_ctrl_thread, NULL, controll, args);
	while (1)
		eat(&philo);
}

void	create_procceses(t_philo **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		arr[i]->pid = fork();
		if (arr[i]->pid < 0)
			ft_error(SYSCALL_ERR);
		else if (arr[i]->pid == 0)
		{
			philo_start(arr[i]);
			exit (0);
		}
		++i;
	}
}

t_philo	**get_philo_arr(t_philo *head_philo)
{
	t_philo	**arr;
	t_philo	*tmp;
	int 	i;

	arr = malloc(sizeof(t_philo *) * (head_philo->args->number + 1));
	if (!arr)
		ft_error(SYSCALL_ERR);
	i = 0;
	tmp = head_philo;
	while(i < head_philo->args->number)
	{
		arr[i] = tmp;
		tmp = tmp->left_philo;
		++i;
	}
	arr[i] = NULL;
	return (arr);
}

int		main(int argc, char **argv, char **env)
{
	t_philo			*head_philo;
	t_controller	*controller;
	t_philo			**philo_arr;
	int				i;

	head_philo = create_philos(argv, argc);
	philo_arr = get_philo_arr(head_philo);
	init_sems(head_philo->args->number);
	create_procceses(philo_arr);
	sem_wait(g_finish);
	i = 0;
	while (controller[i].philo)
	{
		kill(controller[i].philo->pid, SIGQUIT);
		++i;
	}
	unlink_sems();
	return (0);
}
