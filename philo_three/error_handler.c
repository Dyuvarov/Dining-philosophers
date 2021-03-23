/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:04:15 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/23 14:05:11 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
