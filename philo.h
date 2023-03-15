#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef pthread_mutex_t	t_fork;
typedef	struct s_philo	t_philo;
typedef	long long		t_microsec;

typedef struct s_struct
{
	int				p_count;
	t_microsec		time_to_die;
	t_microsec		time_to_eat;
	t_microsec		time_to_sleep;
	int				times_to_eat;
	int				has_sim_ended;
	t_microsec		start_time;
	t_philo			*philosophers;
	pthread_mutex_t	sim_state;
	pthread_mutex_t	*forks;	
}				t_struct;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_microsec		last_eaten;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	t_struct		*args;
}				t_philo;

int		ft_atoi(const char *str);
int		parse_args(int argc, char **argv, t_struct *args);
int		check_valid_argument(char *str);
int		check_if_argument_above_zero(t_struct *args, int argc);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		create_forks(t_struct *args);
int			create_philos(t_struct *args);
int		create_threads(t_struct *args);
t_microsec	calc_time(t_struct *args);
int		wait_all(t_struct *args);
int		destroy_mutexes(t_struct *args);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		is_dead(t_philo *philosopher, t_microsec time);
int		simulation(t_philo *philosopher);
int		eat(t_philo *philosopher);
int		go_sleep(t_philo *philosopher);
int		philo_wait(t_philo *philosopher, t_microsec arg);

#endif
