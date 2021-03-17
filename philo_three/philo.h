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
sem_t	*g_finish;

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
	int 				pid;
	int 				meals;
	long				last_meal;
	struct s_args		*args;
	struct s_philo		*left_philo;
	struct s_philo		*right_philo;
	char 				*sem_name;
	sem_t				*meal_sem;
}				t_philo;


int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_strlen(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_error(int code);
t_philo			*create_philos(char	**argv, int argc);
long			get_time();
void			eat(t_philo **ph);
void			*philo_sleep_n_think(void *args);
void			philo_death(t_philo *philo);
void 			init_sems(int philo_num);
void			unlink_sems(t_philo **philo_arr);
void			show_msg(const char * str, long time, int philo_number);
void			*philo_controll(void *args);
void 			*meal_count_controll(void *args);
#endif
