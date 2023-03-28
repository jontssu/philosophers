/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state_and_time_funcs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:22:04 by jole              #+#    #+#             */
/*   Updated: 2023/03/28 16:09:10 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_philo *philosopher, char *state)
{
	if (pthread_mutex_lock(&philosopher->args->sim_state))
		return (-1);
	if (philosopher->args->sim_ended == 0)
	{
		if (!(calc_time(philosopher->args) - philosopher->last_eaten >= \
					philosopher->args->time_to_die))
			printf("%lld %d %s", calc_time(philosopher->args) / 1000, \
					philosopher->id, state);
	}
	else
	{
		pthread_mutex_unlock(&philosopher->args->sim_state);
		return (-1);
	}
	if (pthread_mutex_unlock(&philosopher->args->sim_state))
		return (-1);
	return (0);
}

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

int	go_sleep(t_philo *philosopher)
{
	if (print_state(philosopher, "is sleeping\n"))
		return (-1);
	philo_wait(philosopher, philosopher->args->time_to_sleep);
	return (0);
}
