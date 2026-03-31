/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:56:12 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/31 18:29:54 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_fork(t_philo *philo);

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
		printf("[%ld] philo n°%d has taken a fork\n", final_time,
			philo->id_philo);
	else if (philo->state == IS_EATING)
		printf("[%ld] philo n°%d is eating\n", final_time, philo->id_philo);
	else if (philo->state == IS_SLEEPING)
		printf("[%ld] philo n°%d is sleeping\n", final_time, philo->id_philo);
	else if (philo->state == IS_THINKING)
		printf("[%ld] philo n°%d is thinking\n", final_time, philo->id_philo);
	else if (philo->state == IS_DEAD)
		printf("[%ld] philo n°%d %sdied%s\n", final_time, philo->id_philo,
			RED, NC);
	pthread_mutex_unlock(&philo->data->is_talking);
}

bool	is_taking_fork(t_philo *philo)
{
	if (!unlock_fork(philo))
		return (false);
	pthread_mutex_lock(&philo->protect_meal);
	philo->last_meal = get_time();
	if (philo->meals_counter < philo->data->max_eat)
		philo->meals_counter++;
	pthread_mutex_unlock(&philo->protect_meal);
	pthread_mutex_lock(&philo->data->mutex_state);
	philo->state = IS_EATING;
	print_states(philo);
	pthread_mutex_unlock(&philo->data->mutex_state);
	precise_sleep(philo->data->time_to_eat);
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
	else
		lock_fork(philo);
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

static void	lock_fork(t_philo *philo)
{
	if ((philo->id_philo % 2) != 0)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(&philo->data->mutex_state);
		philo->state = IS_TAKING_FORK;
		print_states(philo);
		pthread_mutex_unlock(&philo->data->mutex_state);
		pthread_mutex_lock(philo->fork_right);
		print_states(philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(&philo->data->mutex_state);
		philo->state = IS_TAKING_FORK;
		print_states(philo);
		pthread_mutex_unlock(&philo->data->mutex_state);
		pthread_mutex_lock(philo->fork_left);
		print_states(philo);
	}
}
