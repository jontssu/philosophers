/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:44:17 by jole              #+#    #+#             */
/*   Updated: 2023/03/08 18:58:31 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	int	i;
	
	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		th[8];
	int				i;
	t_struct		args;
	pthread_mutex_t	mutex;

	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid amount of arguments", 28);
		exit(-1);
	}
	parse_args(argc, argv, &args);
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 8)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			write(2, "Failed to create thread", 23);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		i++;
	}
	printf("Number of mails: %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}
