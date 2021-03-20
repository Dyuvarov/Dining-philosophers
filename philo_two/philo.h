/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:37:15 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/14 14:43:51 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNTITLED_PHILO_H
# define UNTITLED_PHILO_H

# include <pthread.h>
# include <semaphore.h>

# define ARGS_ERR		100
# define SYSCALL_ERR	101

typedef struct	s_args
{
	int number;
	int die_time;
	int eat_time;
	int sleep_time;
	int eat_num;
	sem_t	*forks_sem;
	sem_t	*output_sem;
}				t_args;

typedef struct	s_philo
{
	int					number;
	long				last_meal;
	pthread_t			*thread;
	struct s_args		*args;
	struct s_controller	*cntrl;
	struct s_philo		*left_philo;
	struct s_philo		*right_philo;
	sem_t			*meal_sem;
}				t_philo;

typedef struct	s_controller
{
	t_philo	*philo;
	int		meals;
}				t_controller;

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_strlen(const char *str);
void			ft_error(int code);
t_philo			*create_philos(char	**argv, int argc);
long			get_time();
void			eat(t_philo **ph);
void			*philo_sleep_n_think(void *args);
void			philo_death(t_philo *philo);
sem_t 			*init_sem(char *name, int value);
void			unlink_sems(t_philo *philo);
void			show_msg(const char * str, long time, t_philo *philo);
#endif
