/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:36:55 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/14 14:31:26 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "unistd.h"
#include <stdlib.h>

void	ft_error(int code)
{
	if (code == ARGS_ERR)
		write(2, "ERROR: Wrong options!\n",
			ft_strlen("ERROR: Wrong options!\n"));
	else if (code == SYSCALL_ERR)
		write(2, "ERROR: system call failed!\n",
			ft_strlen("ERROR: system call failed!\n"));
	exit(EXIT_FAILURE);
}
