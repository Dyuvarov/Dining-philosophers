#ifndef UNTITLED_PHILO_H
# define UNTITLED_PHILO_H

# include <pthread.h>
# include <semaphore.h>

# define ARGS_ERR		100
# define SYSCALL_ERR	101

typedef struct	s_args
{
	int		number;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_num;
	long	start_t;
	sem_t	*forks_sem;
	sem_t	*output_sem;
	sem_t	*finish_sem;
}				t_args;

typedef struct	s_philo
{
	int					number;
	int					pid;
	int					meals;
	long				last_meal;
	struct s_args		*args;
	struct s_philo		*left_philo;
	struct s_philo		*right_philo;
	char				*sem_name;
	char				*meal_sem_name;
	sem_t				*meal_count_sem;
	sem_t				*meal_sem;
}				t_philo;

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_strlen(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_error(int code, t_args *args);
t_philo			*create_philos(t_args *args);
long			get_time(long start);
void			eat(t_philo **ph);
void			*philo_sleep_n_think(void *args);
void			philo_death(t_philo *philo);
t_args			*initialize_args(char **argv, int argc);
sem_t			*init_sem(char *name, int value);
void			unlink_sems(t_args *args);
void			show_msg(const char *str, long time, t_philo *philo);
void			*philo_controll(void *args);
void			*meal_count_controll(void *args);
#endif
