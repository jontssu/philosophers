/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:44:17 by jole              #+#    #+#             */
/*   Updated: 2023/03/23 15:59:40 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philosopher, t_microsec time)
{
	if (pthread_mutex_lock(&philosopher->args->sim_state))
		return (-1);
	if (time - philosopher->last_eaten >= philosopher->args->time_to_die)
	{
		if (philosopher->args->sim_ended == 0)
			printf("%lld %d died\n", time / 1000, philosopher->id);
		philosopher->args->sim_ended = 1;
		pthread_mutex_unlock(&philosopher->args->sim_state);
		return (1);
	}
	if (pthread_mutex_unlock(&philosopher->args->sim_state))
		return (-1);
	return (0);
}

int	monitor(t_struct *args)
{
	int			i;
	int			game_has_ended;

	game_has_ended = 0;
	while (game_has_ended == 0)
	{
		i = 0;
		while (i < args->p_count)
		{
			if (is_dead(&args->philosopher[i], calc_time(args)) || \
					enough_times_eaten_check(args))
			{
				if (pthread_mutex_lock(&args->sim_state))
					return (-1);
				game_has_ended = 1;
				if (pthread_mutex_unlock(&args->sim_state))
					return (-1);
				return (0);
			}
			i++;
		}
		usleep(5000);
	}
	return (0);
}

int	enough_times_eaten_check(t_struct *args)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (args->times_to_eat > 0)
	{
		while (i < args->p_count)
		{
			if (args->philosopher[i].times_eaten >= args->times_to_eat)
				x++;
			i++;
		}
		if (x == args->p_count)
		{
			args->sim_ended = 1;
			return (1);
		}
		return (0);
	}
	return (0);
}

int	print_state(t_philo *philosopher, char *state)
{
	if (pthread_mutex_lock(&philosopher->args->sim_state))
		return (-1);
	if (philosopher->args->sim_ended == 0)
	{
		if (!(calc_time(philosopher->args) - philosopher->last_eaten >= philosopher->args->time_to_die))
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

int	main(int argc, char **argv)
{
	t_struct		args;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid amount of arguments");
		return (0);
	}
	memset(&args, 0, sizeof(t_struct));
	if (parse_args(argc, argv, &args) == -1)
		return (-1);
	if (create_forks(&args) == -1)
		return (-1);
	if (create_philos(&args) == -1)
		return (-1);
	if (pthread_mutex_init(&args.sim_state, NULL))
		return (-1);
	if (pthread_mutex_lock(&args.sim_state))
		return (-1);
	if (create_threads(&args) == -1)
		return (-1);
	if (calc_time(&args) == 1)
		return (-1);
	if (pthread_mutex_unlock(&args.sim_state))
		return (-1);
	if (monitor(&args))
		return (-1);
	if (wait_all(&args) == -1)
		return (-1);
	if (destroy_mutexes(&args) == -1)
		return (-1);
	return (0);
}
