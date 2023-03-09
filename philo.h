#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef pthread_mutex_t t_fork;
typedef	struct s_philo t_philo;

typedef struct s_struct
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				id;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;	
}				t_struct;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
}				t_philo;

int	ft_atoi(const char *str);
int	parse_args(int argc, char **argv, t_struct *args);
int	check_valid_argument(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isdigit(int c);
int	create_forks(t_struct *args);
int	create_philos(t_struct *args);
int	create_threads(t_struct *args);
int	wait_all(t_struct *args);
int	destroy_mutexes(t_struct *args);

#endif
