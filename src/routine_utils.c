#include "philo.h"

void	creat_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].ID, NULL, start_routine, &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, &data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].ID, NULL);
		i++;
	}
}

void	*monitor_routine(void	*param)
{
	t_data *data;
	struct timeval	time;
	int				i;
	size_t			actual_time;

	data = param;
	actual_time = 0;
	i = 0;
	while(1)
	{
		memset(&time, 0, sizeof(struct timeval));
		gettimeofday(&time, NULL);
		actual_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		pthread_mutex_lock(&data->philos[i].protect_meal);
			if ((actual_time - data->philos[i].last_meal) > data->time_to_die)
			{
				data->philos[i].state = IS_DEAD;
				pthread_mutex_lock(&data->simul);
				data->is_running = false;
				pthread_mutex_unlock(&data->simul);
				pthread_mutex_unlock(&data->philos[i].protect_meal);
				break ;
			}
		pthread_mutex_unlock(&data->philos[i].protect_meal);
		usleep(1000);
		i++;
		if (i == data->nb_philo)
			i = 0;
	}
}
