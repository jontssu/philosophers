/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:44:17 by jole              #+#    #+#             */
/*   Updated: 2023/03/09 20:32:19 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_struct		args;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid amount of arguments");
		return (0);
	}
	if (parse_args(argc, argv, &args) == -1)
		return (-1);
	memset(&args, 0, sizeof(args));
	if (create_forks(&args) == -1)
		return (-1);
	if (create_threads(&args) == -1)
		return (-1);
	if (wait_all(&args) == -1)
		return (-1);
	if (destroy_mutexes(&args) == - 1)
		return (-1);
	return (0);
}
