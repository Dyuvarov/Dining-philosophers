#include "philo.h"
#include <stdio.h>

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
		ft_error(SYSCALL_ERR);
}

void	unlink_sems(void)
{
	sem_unlink("forks");
	sem_unlink("output");
}