/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:08:29 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/03/23 14:08:36 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "philo.h"

static int	nlen(int n)
{
	int		i;
	long	ncpy;

	ncpy = n;
	i = 0;
	while (ncpy > 0)
	{
		ncpy /= 10;
		i++;
	}
	return (i);
}

static void	reverse_string(char *s, int len)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	ncpy;
	int		i;

	len = nlen(n);
	ncpy = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (ncpy > 0)
	{
		str[i] = (ncpy % 10) + '0';
		ncpy /= 10;
		i++;
	}
	str[i] = '\0';
	reverse_string(str, len);
	return (str);
}

static int	add_str(char *result, char const *s, int k)
{
	int j;

	j = 0;
	while (s[j])
	{
		result[k] = s[j];
		j++;
		k++;
	}
	return (k);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	int				k;

	if (!s1 || !s2)
		return (NULL);
	k = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result)
	{
		k = add_str(result, s1, k);
		k = add_str(result, s2, k);
		result[k] = '\0';
	}
	return (result);
}
