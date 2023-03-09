/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fork_and_philos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:21:14 by jole              #+#    #+#             */
/*   Updated: 2023/03/09 17:46:05 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_struct *args)
{
	int	i;

	i = 0;
	args->forks = ft_calloc(args->philos * sizeof(pthread_mutex_t));
	if (!args->forks)
		return (-1);
	while (i < args->philos)
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
	int	i;

	i = 0;
	args->philosophers = ft_calloc(args->philos * (sizeof)t_philo);
	while (i < args->philos)
	{
		args->philosophers[i].philo = i + 1;
		if (i + 1 < args->philos)
			args->philosophers[i].right = &args->forks[i];
		else
			args->philosophers[i].right = &args->forks[0];
		if (i)
			args->philosophers[i].left = &args->forks[i - 1];
		else
			args->philosophers[i].left = &args->forks[args->philos - 1];
		i++;
	}
	return (0);
}

int	create_threads(t_struct *args)
{
	int		i;

	i = 0;
	while (i < args->philos)
	{
		if (pthread_create(args->philo + i, NULL, &routine, args) != 0)
		{
			printf("Failed to create thread");
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
	while (i < args->philos)
	{
		if (pthread_join(args->philo[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	destroy_mutexes(t_struct *args)
{
	int	i;

	i = 0;
	while (i < args->philos)
	{
		if (!pthread_mutex_destroy(&args->forks[i]))
			return (-1);	
		i++;
	}
	return (0);
}
