#include "philo.h"
#include <stdio.h>
#include <fcntl.h>

void 	show_msg(const char *str, long time, t_philo *philo)
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
	int	i;

	i = 1;
	while (i <= args->number)
	{
		sem_unlink(ft_itoa(i));
		++i;
	}
	sem_unlink("forks");
	sem_unlink("output");
}
