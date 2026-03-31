/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:56:14 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/31 18:27:51 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor_routine(void *param);
static void	*start_routine(void *data);
static bool	check_death(t_data *data, int i, size_t actual_time);
static void	possible_sleep(t_philo *philo);

void	creat_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].id, NULL, start_routine,
			&data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].id, NULL);
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
		if (!check_death(data, i, actual_time))
			break ;
		if (data->max_eat > 0)
			if (check_max_meal(data))
				break ;
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
	while (1)
	{
		if (!check_is_running(philo))
			break ;
		if (!is_taking_fork(philo))
			break ;
		pthread_mutex_lock(&philo->data->mutex_state);
		philo->state = IS_SLEEPING;
		print_states(philo);
		pthread_mutex_unlock(&philo->data->mutex_state);
		precise_sleep(philo->data->time_to_sleep);
		if (!check_is_running(philo))
			break ;
		pthread_mutex_lock(&philo->data->mutex_state);
		philo->state = IS_THINKING;
		print_states(philo);
		pthread_mutex_unlock(&philo->data->mutex_state);
		possible_sleep(philo);
	}
	return (NULL);
}

static bool	check_death(t_data *data, int i, size_t actual_time)
{
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
		return (false);
	}
	pthread_mutex_unlock(&data->philos[i].protect_meal);
	return (true);
}

static void	possible_sleep(t_philo *philo)
{
	if ((philo->data->time_to_die - philo->data->time_to_eat
			- philo->data->time_to_sleep) > ((philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep))
		precise_sleep((philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep);
}
