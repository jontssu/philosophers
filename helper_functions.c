/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:15:44 by jole              #+#    #+#             */
/*   Updated: 2023/03/24 15:23:14 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	bytes;

	bytes = count * size;
	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (bytes / count != size)
		return (0);
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

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

int	ft_atoi(const char *str)
{
	long long	nb;
	int			is_negative;

	nb = 0;
	is_negative = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_negative = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str++ - 48);
		if (nb < 0)
		{
			if (is_negative == 1)
				return (-1);
			return (0);
		}
	}
	return (nb * is_negative);
}
