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

sem_t	*g_forks;
sem_t	*g_output;

typedef struct	s_args
{
	int number;
	int die_time;
	int eat_time;
	int sleep_time;
	int eat_num;
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
}				t_philo;

typedef struct	s_controller
{
	t_philo	*philo;
	int		meals;
}				t_controller;

int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
void			ft_error(int code);
t_philo			*create_philos(char	**argv, int argc);
long			get_time();
void			eat(t_philo **ph);
void			*philo_sleep_n_think(void *args);
void			philo_death(t_philo *philo);
void 			init_sems(int philo_num);
void			unlink_sems(void);
void			show_msg(const char * str, long time, int philo_number);
#endif