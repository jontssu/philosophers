#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>

typedef pthread_mutex_t t_fork;

typedef struct s_struct
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				id;
	pthread_mutex_t	*forks;	
	pthread_t		*philo;
}				t_struct;

int	ft_atoi(const char *str);
int	parse_args(int argc, char **argv, t_struct *args);
int	check_valid_argument(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isdigit(int c);
int	create_forks(t_struct *args);

#endif
