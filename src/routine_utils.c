/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:56:12 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/26 09:26:33 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	current_time = get_time();
	final_time = current_time - philo->data->start_time;
	if (!check_is_running(philo))
		return ;
	pthread_mutex_lock(&philo->data->is_talking);
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

bool	is_taking_fork(t_philo *philo)
{
	if (!unlock_fork(philo))
		return (false);
	pthread_mutex_lock(&philo->data->mutex_state);
	philo->state = IS_TAKING_FORK;
	pthread_mutex_unlock(&philo->data->mutex_state);
	pthread_mutex_lock(&philo->protect_meal);
	philo->last_meal = get_time();
	if (philo->meals_counter < philo->data->max_eat)
		philo->meals_counter++;
	pthread_mutex_unlock(&philo->protect_meal);
	print_states(philo);
	pthread_mutex_lock(&philo->data->mutex_state);
	philo->state = IS_EATING;
	pthread_mutex_unlock(&philo->data->mutex_state);
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

bool	check_max_meal(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].protect_meal);
		if (data->philos[i].meals_counter >= data->max_eat)
			count++;
		pthread_mutex_unlock(&data->philos[i].protect_meal);
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
