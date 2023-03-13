/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fork_and_philos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:21:14 by jole              #+#    #+#             */
/*   Updated: 2023/03/13 20:30:17 by jole             ###   ########.fr       */
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

void	*routine(void *philosopher)
{
	t_philo	*ptr;

	ptr = (t_philo *)philosopher;
	if (pthread_mutex_lock(&ptr->args->sim_state))
		return (0);
	if (pthread_mutex_unlock(&ptr->args->sim_state))
		return (0);
	simulation(ptr);
	return (0);
}

int	simulation(t_philo *philosopher)
{
	t_microsec	time;

//	while
	time = calc_time(philosopher->args);
	printf("%lld %d Is thinking\n", time / 1000, philosopher->id);
	eat(philosopher);
//	sleep
	return (0);
}

int	eat(t_philo *philosopher)
{
	t_microsec	time;

	if (pthread_mutex_lock(philosopher->right))
		return (-1);
	if (pthread_mutex_lock(philosopher->left))
		return (-1);
	time = calc_time(philosopher->args);
	printf("%lld %d Is eating\n", time / 1000, philosopher->id);
	philo_wait(philosopher);
	if (pthread_mutex_unlock(philosopher->right))
		return (-1);
	if (pthread_mutex_unlock(philosopher->left))
		return (-1);
	return (0);
}

int	philo_wait(t_philo *philosopher)
{
	t_microsec	time;

	time = calc_time(philosopher->args);
	while (philosopher->args->start_time < time + philosopher->args->time_to_eat)
	{
		usleep(100);
	}
	return (0);
}

size_t	calc_time(t_struct *args)
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
		args->philosophers[i].args = args;
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
		if (pthread_create(&args->philosophers[i].thread, NULL, routine, &args->philosophers[i]) != 0)
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
