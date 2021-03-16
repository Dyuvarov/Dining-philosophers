#include "philo.h"
#include <sys/time.h>

int			ft_strlen(const char *str)
{
	unsigned long	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long		get_time(void)
{
	struct timeval	tv;
	long			result;

	gettimeofday(&tv, NULL);
	result = (long)tv.tv_sec * 1000 + (long)tv.tv_usec / 1000;
	return (result);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\n' ||
		c == ' ' || c == '\r')
		return (1);
	else
		return (0);
}

static int	skip_start(const char *str, int *negative)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		*negative = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	return (i);
}

int			ft_atoi(const char *str)
{
	long	result;
	int		negative;
	int		i;

	result = 0;
	negative = 1;
	i = skip_start(str, &negative);
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	if (result < 0 && negative < 0)
		return (-1);
	else if (result < 0 && negative > 0)
		return (-1);
	else
		return (result * negative);
}
