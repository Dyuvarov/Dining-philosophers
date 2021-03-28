#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

void	ate_enough_msg(t_philo *philo)
{
	sem_wait(philo->args->output_sem);
	write(1, "ALL PHILOSOPHERS ATE ENOUGH\n",
			ft_strlen("ALL PHILOSOPHERS ATE ENOUGH\n"));
	unlink_sems(philo->args);
}

void	show_msg(const char *str, long time, t_philo *philo)
{
	t_args	*arg;

	arg = philo->args;
	sem_wait(arg->output_sem);
	printf(str, time, philo->number);
	sem_post(arg->output_sem);
}

sem_t	*init_sem(char *name, int value)
{
	sem_t	*sem;

	if (!name)
		return (NULL);
	sem = sem_open(name, O_CREAT, 0666, value);
	if (sem == SEM_FAILED)
		return (NULL);
	else
		return (sem);
}

void	unlink_sems(t_args *args)
{
	int		i;
	char	*sem_name;

	i = 1;
	while (i <= args->number)
	{
		sem_name = ft_itoa(i);
		sem_unlink(sem_name);
		free(sem_name);
		++i;
	}
	sem_unlink("forks");
	sem_unlink("output");
}
