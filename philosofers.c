/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:03:47 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/04 10:28:57 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// (i + 1) % nb_philo = nb_philo % nb_philo = 0;  formule pour ne pas faire de depassement de memoire des fourchettes

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			signe *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (signe * result);
}

void	setup_data(t_data *data, int ac, char **av)
{
	data->nb_philo = av[0];
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!fork)
		return (NULL);
	data->time_to_die = av[1];
	data->time_to_eat = av[2];
	data->time_to_sleep = av[3];
	data->max_eat = av[4];
}

void	error_args(void)
{
	printf("Error usage type :\n\t\t <number_of_philosophers time_to_die");
	printf(" time_to_eat time_to_sleep [number_of_times_each_philosopher");
	printf("_must_eat]>\n");
}

int main(int ac, char **av)
{
	t_data data;
	memset(&data, 0, sizeof(data));
	if (ac != 5)
	{
		error_args();
		return (1);
	}
	setup_data(&data, ac, av);
}
