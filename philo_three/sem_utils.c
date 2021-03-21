#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void 	show_msg(const char *str, long time, t_philo *philo)
{
	sem_wait(philo->args->output_sem);
	printf(str, time, philo->number);
	sem_post(philo->args->output_sem);
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

	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("finish");
	if (args)
	{
		i = 1;
		while (i <= (args->number * 2))
		{
			sem_name = ft_itoa(i);
			if (sem_name)
			{
				sem_unlink(sem_name);
				free(sem_name);
			}
			++i;
		}
	}
}

