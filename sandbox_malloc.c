#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NC "\e[0m"
#define YELLOW "\e[1;33m"

long	g_counter = 0;

void	*thread_routine(void *data)
{
	pthread_mutex_t	*mutex;

	mutex = data;
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (g_counter >= 1000)
		{
			pthread_mutex_unlock(mutex);
			break ;
		}
		g_counter++;
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t		tid1;
	pthread_t		tid2;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&tid1, NULL, thread_routine, &mutex);
	pthread_create(&tid2, NULL, thread_routine, &mutex);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("g_counter = [%ld]\n", YELLOW, g_counter);
	pthread_mutex_destroy(&mutex);
	return (0);
}
