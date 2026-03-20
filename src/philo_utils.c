#include "philo.h"
static void	init_mutex(t_data *data);

bool	setup_data(t_data *data, char **av, int ac)
{
	data->nb_philo = ft_atol(av[1]);
	if (data->nb_philo < 0 || data->nb_philo > INT_MAX)
		return (false);
	data->fork = safe_calloc(data->nb_philo, sizeof(pthread_mutex_t));
	init_mutex(data);
	data->time_to_die = ft_atol(av[2]);
	if (data->time_to_die > INT_MAX)
		return (false);
	data->time_to_eat = ft_atol(av[3]);
	if (data->time_to_eat > INT_MAX)
		return (false);
	data->time_to_sleep = ft_atol(av[4]);
	if (data->time_to_sleep >INT_MAX)
		return (false);
	if (ac == 6)
	{
		data->max_eat = ft_atol(av[5]);
		if (data->max_eat < 0 || data->max_eat > INT_MAX)
			return (false);
	}
	return (true);
}

void	setup_philo(t_data *data)
{
	int	i;
	struct timeval	actual_time;

	memset(&actual_time, 0, sizeof(struct timeval));
	gettimeofday(&actual_time, NULL);
	i = 0;
	data->philos = safe_calloc(data->nb_philo, sizeof(t_philo));
	while(i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id_philo = i + 1;
		data->philos[i].fork_right = &data->fork[i];
		data->philos[i].fork_left = &data->fork[(i + 1) % data->nb_philo];
		data->philos[i].last_meal = (actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000);
		i++;
	}
	memset(&actual_time, 0, sizeof(struct timeval));
}

static void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->is_talking, NULL) != 0 )
		ft_error("initialization Mutex failed\n");
	if (pthread_mutex_init(&data->simul, NULL) != 0)
		ft_error("initialization Mutex failed\n");
	while (i < (data->nb_philo))
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == 0)
			i++;
		else
			ft_error("initialization Mutex failed\n");
	}
}
