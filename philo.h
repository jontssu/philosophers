/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:39:41 by jole              #+#    #+#             */
/*   Updated: 2023/03/24 15:42:30 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef pthread_mutex_t	t_fork;
typedef struct s_philo	t_philo;
typedef long long		t_microsec;

typedef struct s_struct
{
	int				p_count;
	t_microsec		time_to_die;
	t_microsec		time_to_eat;
	t_microsec		time_to_sleep;
	int				times_to_eat;
	int				sim_ended;
	t_microsec		start_time;
	t_philo			*philosopher;
	pthread_mutex_t	sim_state;
	pthread_mutex_t	*forks;	
}				t_struct;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				times_eaten;
	t_microsec		last_eaten;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_struct		*args;
}				t_philo;

int			parse_args(int argc, char **argv, t_struct *args);
int			check_valid_argument(char *str);
int			check_if_argument_above_zero(t_struct *args, int argc);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isdigit(int c);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			create_all(t_struct *args);
int			create_forks(t_struct *args);
int			create_philos(t_struct *args);
int			create_threads(t_struct *args);
int			wait_all(t_struct *args);
int			destroy_mutexes(t_struct *args);
int			is_dead(t_philo *philosopher, t_microsec time);
int			enough_times_eaten_check(t_struct *args);
int			monitor(t_struct *args);
int			simulation(t_philo *philosopher);
void		*routine(void *philosopher);
void		set_forks(t_fork **fork1, t_fork **fork2, t_philo *philosopher);
int			pick_up_forks(t_philo *philosopher);
int			eat(t_philo *philosopher, t_fork *fork1, t_fork *fork2);
int			return_forks(t_fork *fork1, t_fork *fork2);
int			print_state(t_philo *philosopher, char *state);
t_microsec	calc_time(t_struct *args);
int			philo_wait(t_philo *philosopher, t_microsec arg);
int			go_sleep(t_philo *philosopher);

#endif
