#include "philo.h"

long	ft_atol(const char *str)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (!check_str(str))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	return (nb * sign);
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

void	error_args(void)
{
	printf("Error usage type :\n\t\t <number_of_philosophers time_to_die");
	printf(" time_to_eat time_to_sleep [number_of_times_each_philosopher");
	printf("_must_eat]>\n");
	exit (EXIT_FAILURE);
}
