#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void 	show_msg(const char *str, long time, int philo_number)
{
	sem_wait(g_output);
	printf(str, time, philo_number);
	sem_post(g_output);
}

void	init_sems(int philo_num)
{
	g_forks = sem_open("forks", O_CREAT, 0666, (philo_num / 2));
	if (g_forks == SEM_FAILED)
		ft_error(SYSCALL_ERR);
	g_output = sem_open("output", O_CREAT, 0666, 1);
	if (g_output == SEM_FAILED)
	{
		sem_unlink("forks");
		ft_error(SYSCALL_ERR);
	}
	g_finish = sem_open("finish", O_CREAT, 0666, 0);
	if (g_finish == SEM_FAILED)
	{
		sem_unlink("forks");
		sem_unlink("output");
		ft_error(SYSCALL_ERR);
	}
}

void	unlink_sems(t_philo **philo_arr)
{
	int i;

	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("finish");
	i = 0;
	while (philo_arr[i])
	{
		sem_unlink(philo_arr[i]->sem_name);
		free(philo_arr[i]->sem_name);
		++i;
	}
}

