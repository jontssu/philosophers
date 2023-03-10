/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fork_and_philos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:21:14 by jole              #+#    #+#             */
/*   Updated: 2023/03/11 01:53:01 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_struct *args)
{
	int	i;

	i = 0;
	args->forks = ft_calloc(args->p_count, sizeof(pthread_mutex_t));
	if (!args->forks)
		return (-1);
	while (i < args->p_count)
	{
		if (pthread_mutex_init(&args->forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

void	*routine(void *args)
{
	t_struct	*ptr;

	ptr = (t_struct *)args;
	return (0);
}

int	create_philos(t_struct *args)
{
	int		i;

	i = 0;
	args->philosophers = ft_calloc(args->p_count, sizeof(t_philo));
	if (!args->philosophers)
		return (-1);
	while (i < args->p_count)
	{
		args->philosophers[i].id = i + 1;
		if (i + 1 < args->p_count)
			args->philosophers[i].right = &args->forks[i];
		else
			args->philosophers[i].right = &args->forks[0];
		if (i)
			args->philosophers[i].left = &args->forks[i - 1];
		else
			args->philosophers[i].left = &args->forks[args->p_count - 1];
		i++;
	}
	return (0);
}

int	create_threads(t_struct *args)
{
	int		i;

	i = 0;
	while (i < args->p_count)
	{
		if (pthread_create(&(args->philosophers[i].thread), NULL, &routine, &args->philosophers[i]) != 0)
		{
			printf("Failed to create a thread");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	wait_all(t_struct *args)
{
	int	i;

	i = 0;
	while (i < args->p_count)
	{
		if (pthread_join(args->philosophers[i].thread, NULL) != 0)
		{
			printf("Failed to join a thread");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	destroy_mutexes(t_struct *args)
{
	int	i;

	i = 0;
	while (i < args->p_count)
	{
		if (!pthread_mutex_destroy(&args->forks[i]))
			return (-1);	
		i++;
	}
	return (0);
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
