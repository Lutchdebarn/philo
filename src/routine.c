#include "philo.h"

static void	is_taking_fork(t_philo *philo);
static void	*monitor_routine(void *param);
static void	*start_routine(void *data);

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

static void	*monitor_routine(void *param)
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
			data->philos[i].data->is_running = false;
			pthread_mutex_lock(&data->simul);
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
	return (NULL);
}

static void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = data;
	while(1)
	{
		pthread_mutex_lock(&philo->data->simul);
		if (!philo->data->is_running)
		{
			pthread_mutex_unlock(&philo->data->simul);
			break ;
		}
		pthread_mutex_unlock(&philo->data->simul);
		is_taking_fork(philo);
		philo->state = IS_SLEEPING;
		print_states(philo);
		usleep(philo->data->time_to_sleep * 1000);
		philo->state = IS_THINKING;
		print_states(philo);
	}
	return (NULL);
}

void	print_states(t_philo *philo)
{
	struct timeval	time;
	size_t			current_time;
	size_t			final_time;

	memset(&time, 0, sizeof(struct timeval));
	gettimeofday(&time, NULL);
	current_time = 0;
	final_time = 0;
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	final_time = current_time - philo->last_meal;
	pthread_mutex_lock(&philo->data->is_talking);
	if (philo->state == IS_TAKING_FORK)
		printf("[%ld] philo n°%d has taken a fork\n", final_time, philo->id_philo);
	else if (philo->state == IS_EATING)
	{
		printf("[%ld] philo n°%d is eating\n", final_time, philo->id_philo);
	}
	else if (philo->state == IS_SLEEPING)
		printf("[%ld] philo n°%d is sleeping\n", final_time, philo->id_philo);
	else if (philo->state == IS_THINKING)
		printf("[%ld] philo n°%d is thinking\n", final_time, philo->id_philo);
	else if (philo->state == IS_DEAD)
		printf("[%ld] philo n°%d died.. RIP\n", final_time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->is_talking);
}

static void	is_taking_fork(t_philo *philo)
{
	if ((philo->id_philo % 2) != 0)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(philo->fork_left);
	}
		philo->state = IS_TAKING_FORK;
		print_states(philo);
		philo->state = IS_EATING;
		print_states(philo);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
}
