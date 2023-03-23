/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:15:44 by jole              #+#    #+#             */
/*   Updated: 2023/03/23 15:43:46 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_wait(t_philo *philosopher, t_microsec arg)
{
	t_microsec	time;

	time = calc_time(philosopher->args);
	while (time + arg > calc_time(philosopher->args))
	{
		usleep(500);
	}
	return (0);
}

t_microsec	calc_time(t_struct *args)
{
	struct timeval	tv;
	t_microsec		time;

	if (gettimeofday(&tv, NULL))
		return (1);
	time = (tv.tv_sec * 1000 * 1000) + tv.tv_usec;
	if (args->start_time == 0)
		args->start_time = time;
	return (time - args->start_time);
}

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
