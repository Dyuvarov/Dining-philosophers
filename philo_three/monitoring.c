#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	*philo_controll(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while(1)
	{
		if ((get_time() - philo->last_meal) > philo->args->die_time)
			philo_death(philo);
		if (philo->args->eat_num >= 0 && (philo->meals >= philo->args->eat_num))
			sem_post(philo->meal_sem);
	}
	return (NULL);
}

void 	*meal_count_controll(void *args)
{
	t_philo	*head_philo;
	t_philo	*tmp;
	int		i;

	i = 0;
	head_philo = (t_philo *)args;
	tmp = head_philo;
	while(i < head_philo->args->number)
	{
		sem_wait(tmp->meal_sem);
		tmp = tmp->left_philo;
		++i;
	}
	sem_wait(g_output);
	write(1, "ALL PHILOSOPHERS ATE ENOUGH\n", ft_strlen("ALL PHILOSOPHERS ATE ENOUGH\n"));
	sem_post(g_output);
	sem_post(g_finish);
	return (NULL);
}