# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>

pthread_mutex_t *init_table_forks(int nb_philo)
{
	pthread_mutex_t	*fork;
	int i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!fork)
		return (NULL);
	while (i < nb_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return(fork);
}

int main(void)
{
	int nb_philo = 5;
}
