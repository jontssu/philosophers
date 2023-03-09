/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:25:31 by jole              #+#    #+#             */
/*   Updated: 2023/03/09 15:12:58 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_struct *args)
{
	int	i;

	i = 0
	while (i < args->philos)
	{
		if (pthread_mutex_init(&args->forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	create_philos(t_struct *args)
{
	int	i;

	i = 0;
	while (i < args->philos)
	{
		if (
		i++;
	}
}
