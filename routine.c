/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:11:25 by jole              #+#    #+#             */
/*   Updated: 2023/03/23 15:48:26 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int			first;

	first = 0;
	while (1)
	{
		time = calc_time(philosopher->args);
		if (is_dead(philosopher, time))
			return (0);
		if (print_state(philosopher, "is thinking\n"))
			return (-1);
		if (first == 0)
		{
			if (philosopher->id % 2 == 0)
				usleep(philosopher->args->time_to_eat - 5000);
			first = 1;
		}
		else if (philosopher->args->p_count % 2 == 1)
			philo_wait(philosopher, philosopher->args->time_to_eat - 5000);
		if (eat(philosopher))
			return (-1);
		if (go_sleep(philosopher))
			return (-1);
	}
	return (0);
}

void	set_forks(t_fork **fork1, t_fork **fork2, t_philo *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		*fork1 = philosopher->right;
		*fork2 = philosopher->left;
	}
	else
	{
		*fork1 = philosopher->left;
		*fork2 = philosopher->right;
	}
}

int	eat(t_philo *philosopher)
{
	t_fork	*fork1;
	t_fork	*fork2;

	set_forks(&fork1, &fork2, philosopher);
	if (pthread_mutex_lock(fork1))
		return (-1);
	if (print_state(philosopher, "has taken a fork\n"))
	{
		pthread_mutex_unlock(fork1);
		return (-1);
	}
	if (fork1 == fork2)
	{
		pthread_mutex_unlock(fork1);
		return (-1);
	}
	if (pthread_mutex_lock(fork2))
		return (-1);
	if (print_state(philosopher, "has taken a fork\n"))
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
		return (-1);
	}
	if (print_state(philosopher, "is eating\n"))
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
		return (-1);
	}
	if (is_dead(philosopher, calc_time(philosopher->args)))
		return (-1);
	if (pthread_mutex_lock(&philosopher->args->sim_state))
		return (-1);
	philosopher->last_eaten = calc_time(philosopher->args);
	philosopher->times_eaten += 1;
	if (pthread_mutex_unlock(&philosopher->args->sim_state))
		return (-1);
	philo_wait(philosopher, philosopher->args->time_to_eat);
	if (pthread_mutex_unlock(fork1))
		return (-1);
	if (pthread_mutex_unlock(fork2))
		return (-1);
	return (0);
}

int	go_sleep(t_philo *philosopher)
{
	if (print_state(philosopher, "is sleeping\n"))
		return (-1);
	philo_wait(philosopher, philosopher->args->time_to_sleep);
	return (0);
}
