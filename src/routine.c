#include "philo.h"

static bool	is_taking_fork(t_philo *philo);
static void	*monitor_routine(void *param);
static void	*start_routine(void *data);
static bool	check_max_meal(t_data *data);
bool		unlock_fork(t_philo *philo);

void	creat_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].ID, NULL, start_routine,
			&data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].ID, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}

static void	*monitor_routine(void *param)
{
	t_data	*data;
	int		i;
	size_t	actual_time;

	data = param;
	i = 0;
	while (1)
	{
		actual_time = get_time();
		pthread_mutex_lock(&data->philos[i].protect_meal);
		if ((actual_time - data->philos[i].last_meal) > data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_state);
			data->philos[i].state = IS_DEAD;
			print_states(&data->philos[i]);
			pthread_mutex_unlock(&data->mutex_state);
			pthread_mutex_lock(&data->simul);
			data->philos[i].data->is_running = false;
			pthread_mutex_unlock(&data->simul);
			pthread_mutex_unlock(&data->philos[i].protect_meal);
			break ;
		}
		if (data->max_eat > 0)
			if (check_max_meal(data))
				break ;
		pthread_mutex_unlock(&data->philos[i].protect_meal);
		usleep(1000);
		i++;
		if (i == data->nb_philo)
			i = 0;
	}
	pthread_mutex_unlock(&data->philos[i].protect_meal);
	return (NULL);
}

static bool	check_max_meal(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_counter >= data->max_eat)
			count++;
		i++;
	}
	if (data->nb_philo == count)
	{
		pthread_mutex_lock(&data->simul);
		data->is_running = false;
		pthread_mutex_unlock(&data->simul);
		return (true);
	}
	return (false);
}

static void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = data;
	usleep(200);
	while (1)
	{
		if (!check_is_running(philo))
			break ;
		if (!is_taking_fork(philo))
			break ;
		pthread_mutex_lock(&philo->data->mutex_state);
		philo->state = IS_SLEEPING;
		pthread_mutex_unlock(&philo->data->mutex_state);
		print_states(philo);
		usleep(philo->data->time_to_sleep * 1000);
		if (!check_is_running(philo))
			break ;
		philo->state = IS_THINKING;
		if (philo->data->time_to_eat * 2 > philo->data->time_to_sleep)
			usleep(((philo->data->time_to_eat * 2) - philo->data->time_to_sleep)
				* 1000);
		print_states(philo);
	}
	return (NULL);
}

bool	check_is_running(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->simul);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->simul);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->simul);
	return (true);
}

void	print_states(t_philo *philo)
{
	size_t	current_time;
	size_t	final_time;

	current_time = 0;
	final_time = 0;
	current_time = get_time();
	final_time = current_time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->is_talking);
	if (!check_is_running(philo))
	{
		pthread_mutex_unlock(&philo->data->is_talking);
		return ;
	}
	if (philo->state == IS_TAKING_FORK)
		printf("%s[%ld]%s philo n°%d has taken a fork\n", YELLOW, final_time,
			NC, philo->id_philo);
	else if (philo->state == IS_EATING)
		printf("%s[%ld]%s philo n°%d is eating\n", YELLOW, final_time, NC,
			philo->id_philo);
	else if (philo->state == IS_SLEEPING)
		printf("%s[%ld]%s philo n°%d is sleeping\n", YELLOW, final_time, NC,
			philo->id_philo);
	else if (philo->state == IS_THINKING)
		printf("%s[%ld]%s philo n°%d is thinking\n", YELLOW, final_time, NC,
			philo->id_philo);
	else if (philo->state == IS_DEAD)
		printf("%s[%ld]%s philo n°%d %sdied%s\n", YELLOW, final_time, NC,
			philo->id_philo, RED, NC);
	pthread_mutex_unlock(&philo->data->is_talking);
}

static bool	is_taking_fork(t_philo *philo)
{
	if (!unlock_fork(philo))
		return (false);
	philo->state = IS_TAKING_FORK;
	pthread_mutex_lock(&philo->protect_meal);
	philo->last_meal = get_time();
	if (philo->meals_counter < philo->data->max_eat)
		philo->meals_counter++;
	pthread_mutex_unlock(&philo->protect_meal);
	print_states(philo);
	philo->state = IS_EATING;
	print_states(philo);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	if (!check_is_running(philo))
		return (false);
	return (true);
}

bool	unlock_fork(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(&philo->data->mutex_state);
		philo->state = IS_TAKING_FORK;
		print_states(philo);
		pthread_mutex_unlock(&philo->data->mutex_state);
		pthread_mutex_unlock(philo->fork_right);
		return (false);
	}
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
	return (true);
}
