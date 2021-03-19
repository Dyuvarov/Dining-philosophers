/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:37:15 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/16 15:07:23 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNTITLED_PHILO_H
# define UNTITLED_PHILO_H

# include <pthread.h>

# define ARGS_ERR		100
# define SYSCALL_ERR	101

pthread_mutex_t	g_output;

typedef struct	s_args
{
	int 		number;
	int 		die_time;
	int 		eat_time;
	int 		sleep_time;
	int		eat_num;
	long		start_t;
}				t_args;

typedef struct	s_philo
{
	int					number;
	long				last_meal;
	pthread_t			*thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t		*meal_mtx;
	struct s_args		*args;
	struct s_controller	*cntrl;
	struct s_philo		*left_philo;
	struct s_philo		*right_philo;
	int			activated;
}				t_philo;

typedef struct	s_controller
{
	t_philo	*philo;
	int		meals;
}				t_controller;

typedef struct	s_queue
{
	t_philo			*philo;
	struct s_queue	*next;
}				t_queue;

int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
void			ft_error(int code);
t_philo			*create_philos(char	**argv, int argc);
long			get_time(long start);
void			eat(t_philo **ph);
void			*philo_sleep_n_think(void *args);
void			philo_death(t_philo *philo);
#endif
