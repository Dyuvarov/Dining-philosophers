#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void			wait_threads_finish(t_philo *head_philo)
{
	t_philo	*philo;
	int		i;

	philo = head_philo;
	i = 0;
	while (i < head_philo->args->number)
	{
		pthread_join(*(philo->thread), NULL);
		pthread_detach(*(philo->thread));
		philo = philo->left_philo;
		++i;
	}
}

static t_controller	*create_meal_control(t_philo **head_philo)
{
	int				i;
	t_controller	*ctrl;
	t_philo			*ph_tmp;

	ctrl = malloc(sizeof(t_controller) * ((*head_philo)->args->number + 1));
	if (!ctrl)
		ft_error(SYSCALL_ERR);
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

static void			*meals_controll(void *args)
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
		while (ctrl[i].philo && ctrl[i].philo->activated)
		{
			sem_wait(ctrl[i].philo->meal_sem);
			if ((get_time(arg->start_t) - ctrl[i].philo->last_meal) >= (arg->die_time + 9))
				philo_death(ctrl[i].philo);
			sem_post(ctrl[i].philo->meal_sem);	
			if (arg->eat_num >= 0 && (ctrl[i].meals < arg->eat_num))
				flag = 0;
			++i;
		}
		if (arg->eat_num >= 0 && flag)
			break ;
	}
	sem_wait(arg->output_sem);
	write(1, "ALL PHILOSOPHERS ATE ENOUGH\n", ft_strlen("ALL PHILOSOPHERS ATE ENOUGH\n"));
	unlink_sems(arg);
	exit(EXIT_SUCCESS);
}

static void			*philo_start(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	philo->activated = 1;
	while (1)
		eat(&philo);
	return (NULL);
}

int main(int argc, char **argv) {
	t_philo			*head_philo;
	t_philo			*philo;
	pthread_t		meal_ctrl_thread;
	t_controller	*meal_control;
	int				i;
	t_args			*args;
	
	args = initialize_args(argv, argc);
	printf("eat time = %d\n", args->eat_time);
	unlink_sems(args);
	head_philo = create_philos(args);
	meal_control = create_meal_control(&head_philo);
	philo = head_philo;
	i = 0;
	while (i < head_philo->args->number)
	{
		pthread_create(philo->thread, NULL, philo_start, philo);
		philo = philo->left_philo;
		++i;
	}
	pthread_create(&meal_ctrl_thread, NULL, meals_controll, meal_control);
	pthread_join(meal_ctrl_thread, NULL);
	pthread_detach(meal_ctrl_thread);
	wait_threads_finish(head_philo);
	return (0);
}
