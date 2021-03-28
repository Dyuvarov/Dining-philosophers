#include "philo.h"
#include "unistd.h"
#include <stdlib.h>

void	ft_error(int code, t_args *args)
{
	if (code == ARGS_ERR)
		write(2, "ERROR: Wrong options!\n",
			ft_strlen("ERROR: Wrong options!\n"));
	else if (code == SYSCALL_ERR)
		write(2, "ERROR: system call failed!\n",
			ft_strlen("ERROR: system call failed!\n"));
	unlink_sems(args);
	exit(EXIT_FAILURE);
}
