#include "philo.h"
#include <stdlib.h>

t_controller	*create_meal_control(t_philo **head_philo)
{
	int				i;
	t_controller	*ctrl;
	t_philo			*ph_tmp;

	ctrl = malloc(sizeof(t_controller) * ((*head_philo)->args->number + 1));
	if (!ctrl)
		ft_error(SYSCALL_ERR, *head_philo);
	ph_tmp = *head_philo;
	i = 0;
	while (i < ph_tmp->args->number)
	{
		ctrl[i].philo = ph_tmp;
		ctrl[i].meals = 0;
		ph_tmp->cntrl = &ctrl[i];
		ph_tmp = ph_tmp->left_philo;
		++i;
	}
	ctrl[i].philo = NULL;
	return (ctrl);
}

static void		check_death(t_philo *philo, t_args *arg)
{
	if (!(philo->activated))
		return ;
	if ((get_time(arg->start_t) - philo->last_meal) >=
		(arg->die_time + 9))
	{
		philo_death(philo);
	}
}

void			*meals_controll(void *args)
{
	t_controller	*ctrl;
	int				flag;
	int				i;
	t_args			*arg;

	ctrl = (t_controller *)args;
	arg = ctrl[0].philo->args;
	while (1)
	{
		i = 0;
		flag = 1;
		while (ctrl[i].philo)
		{
			pthread_mutex_lock(ctrl[i].philo->meal_mtx);
			check_death(ctrl[i].philo, arg);
			if (arg->eat_num >= 0 && (ctrl[i].meals < arg->eat_num))
				flag = 0;
			pthread_mutex_unlock(ctrl[i].philo->meal_mtx);
			++i;
		}
		if (flag && arg->eat_num >= 0)
			break ;
	}
	ate_enough_msh(ctrl[0].philo);
	exit(EXIT_SUCCESS);
}
