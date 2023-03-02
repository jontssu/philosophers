#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


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
}

int	main()
{
	pthread_t	th[8];
	int		i;
	//struct timeval	current_time;

	/*if (!gettimeofday(&current_time, NULL));
	{
		write(2, "Error\n", 6);
		return (-1);
	}*/
	//printf("seconds: %ld\nmicrosecond: %ld\n", current_time.tv_sec, current_time.tv_usec);
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 8)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			write(2, "Failed to create thread", 23);
			return 1;
		}
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		i++;
	}
	printf("Number of mails: %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}
