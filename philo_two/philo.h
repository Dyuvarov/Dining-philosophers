#ifndef UNTITLED_PHILO_H
# define UNTITLED_PHILO_H

# include <pthread.h>
# include <semaphore.h>

# define ARGS_ERR		100
# define SYSCALL_ERR	101

typedef struct	s_args
{
	int				number;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				eat_num;
	sem_t			*forks_sem;
	sem_t			*output_sem;
	long			start_t;
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
	char				*sem_name;
	sem_t				*meal_sem;
	int					activated;
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
t_controller	*create_meal_control(t_philo **head_philo);
void			*meals_controll(void *args);
void			start_controller(t_philo *head_philo);
t_philo			*create_philos(t_args *args);
long			get_time(long start);
void			eat(t_philo **ph);
void			philo_sleep_n_think(t_philo *philo);
void			philo_death(t_philo *philo);
t_args			*initialize_args(char **argv, int argc);
sem_t			*init_sem(char *name, int value);
void			unlink_sems(t_args *args);
void			show_msg(const char *str, long time, t_philo *philo);
void			ate_enough_msg(t_philo *philo);
#endif
