/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:54:26 by jole              #+#    #+#             */
/*   Updated: 2023/03/08 21:10:43 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 1 && *s1 == *s2 && *s1 != 0 && *s2 != 0)
	{
		n--;
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
void	parse_args(int argc, char **argv, t_struct *args)
{
	int	i;

	i = 0;
	while (i < argc - 1)
 	{
		if (check_valid_argument(argv[1 + i]) == -1)
			exit(-1);
		i++;
	}
	args->philos = ft_atoi(argv[1]);	
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		args->times_to_eat = ft_atoi(argv[5]);
}

int	check_valid_argument(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (-1);
	i = ft_strlen(str);
	if (str[0] == '+')
		i--;
	if (i > 10)
		return (-1);
	else if (i < 10)
		return (0);
	if (str[0] == '+')
		str++;
	if (ft_strncmp(str, "2147483647", 10) > 0)
			return (-1);
	return (0);
}
