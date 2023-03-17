/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutexes_and_threads.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:19:52 by jole              #+#    #+#             */
/*   Updated: 2023/03/17 15:29:25 by jole             ###   ########.fr       */
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

int	create_philos(t_struct *args)
{
	int		i;

	i = 0;
	args->philosopher = ft_calloc(args->p_count, sizeof(t_philo));
	if (!args->philosopher)
		return (-1);
	while (i < args->p_count)
	{
		args->philosopher[i].id = i + 1;
		args->philosopher[i].args = args;
		if (i + 1 < args->p_count)
			args->philosopher[i].right = &args->forks[i];
		else
			args->philosopher[i].right = &args->forks[0];
		if (i)
			args->philosopher[i].left = &args->forks[i - 1];
		else
			args->philosopher[i].left = &args->forks[args->p_count - 1];
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
		if (pthread_create(&args->philosopher[i].thread, NULL, \
				   	routine, &args->philosopher[i]) != 0)
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
		if (pthread_join(args->philosopher[i].thread, NULL) != 0)
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
