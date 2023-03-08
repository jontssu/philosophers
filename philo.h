#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef pthread_mutex_t t_fork;

typedef struct s_struct
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
}				t_struct;

int		ft_atoi(const char *str);
void	parse_args(int argc, char **argv, t_struct *args);
int		check_valid_argument(char *str);

#endif
