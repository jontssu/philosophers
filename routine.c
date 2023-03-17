/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:11:25 by jole              #+#    #+#             */
/*   Updated: 2023/03/17 21:25:17 by jole             ###   ########.fr       */
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
			break ;
		if (print_state(philosopher, "is thinking\n"))
			return (-1);
		if (first == 0)
			first = 1;
		else
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
	if (pthread_mutex_lock(fork2))
		return (-1);
	if (print_state(philosopher, "has taken a fork\n"))
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
		return (-1);
	}
	philosopher->last_eaten = calc_time(philosopher->args);
	if (print_state(philosopher, "is eating\n"))
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
		return (-1);
	}
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

int	print_state(t_philo *philosopher, char *state)
{
	if (pthread_mutex_lock(&philosopher->args->sim_state))
		return (-1);
	if (philosopher->args->has_sim_ended == 0)
		printf("%lld %d %s", calc_time(philosopher->args) / 1000 , philosopher->id, state);
	else
	{
		pthread_mutex_unlock(&philosopher->args->sim_state);
		return (-1);
	}
	if (pthread_mutex_unlock(&philosopher->args->sim_state))
		return (-1);
	return (0);
}
