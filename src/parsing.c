#include "philo.h"

// 1) Check  > INT_MAX
// 2) is number
// 3) timestamps > 60ms

bool	check_str(const char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (false);
	}
	if (i > 10)
		return (false);
	return (true);
}

bool	setup_data(t_data *data, char **av, int ac)
{
	int i;

	i = 0;
	data->nb_philo = ft_atol(av[1]);
	if (data->nb_philo < 0 || data->nb_philo > INT_MAX)
		return (false);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!fork)
		return (NULL);
	init_mutex(data);
	data->time_to_die = ft_atol(av[2]);
	if (data->time_to_die < 0 || data->time_to_die > INT_MAX)
		return (false);
	data->time_to_eat = ft_atol(av[3]);
	if (data->time_to_eat < 0 || data->time_to_eat > INT_MAX)
		return (false);
	data->time_to_sleep = ft_atol(av[4]);
	if (data->time_to_sleep < 0 || data->time_to_sleep >INT_MAX)
		return (false);
	if (ac == 6)
	{
		data->max_eat = ft_atol(av[5]);
		if (data->max_eat < 0 || data->max_eat > INT_MAX)
			return (false);
	}
	return (true);
}

void	safe_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->nb_philo - 1))
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == 0)
			i++;
		else
			ft_error("initialization Mutex failed\n");
	}
}
void	setup_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while(i < data->nb_philo)
	{
		philo[i] = safe_malloc(sizeof(t_philo));
		philo[i]->data = data;
		philo[i]->id_philo = i + 1;
		philo[i]->fork_left = &data->fork[i + 1];
		philo[i]->fork_right = &data->fork[(i + 1) % data->nb_philo];
	}
}
