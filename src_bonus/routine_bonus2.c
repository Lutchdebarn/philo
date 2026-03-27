/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:21:50 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/27 10:44:26 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	is_taking_fork(t_data *data, t_philo *philo);
static void	is_eating(t_data *data, t_philo *philo);
static void	*death_checker(void *param);
static void	is_dead_rip(t_philo *philo, size_t actual_time);

void	start_routine(t_data *data, t_philo *philo)
{
	pthread_create(&philo->thread, NULL, death_checker, philo);
	while (1)
	{
		if (data->max_eat)
			if (philo->meals_counter >= data->max_eat)
				break ;
		sem_wait(data->waiter);
		is_taking_fork(data, philo);
		is_eating(data, philo);
		sem_post(data->waiter);
		pthread_mutex_lock(&philo->mutex_states);
		philo->state = IS_SLEEPING;
		print_states(data, philo);
		pthread_mutex_unlock(&philo->mutex_states);
		usleep(data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->mutex_states);
		philo->state = IS_THINKING;
		pthread_mutex_unlock(&philo->mutex_states);
		if ((data->time_to_die - data->time_to_eat
				- data->time_to_sleep) > ((data->time_to_eat * 2)
				- data->time_to_sleep))
			usleep(((data->time_to_eat * 2) - data->time_to_sleep) * 1000);
	}
	pthread_join(philo->thread, NULL);
	exit(EXIT_SUCCESS);
}

static void	is_eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_meal);
	pthread_mutex_lock(&philo->mutex_states);
	philo->state = IS_EATING;
	print_states(data, philo);
	pthread_mutex_unlock(&philo->mutex_states);
	usleep(data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	if (data->max_eat)
	{
		pthread_mutex_lock(&philo->mutex_meal);
		philo->meals_counter++;
		pthread_mutex_unlock(&philo->mutex_meal);
	}
}

static void	*death_checker(void *param)
{
	t_philo	*philo;
	size_t	actual_time;

	philo = param;
	while (1)
	{
		actual_time = get_time();
		pthread_mutex_lock(&philo->mutex_meal);
		if (philo->data->max_eat > 0
			&& philo->meals_counter >= philo->data->max_eat)
			break ;
		if ((actual_time - philo->last_meal) > philo->data->time_to_die)
		{
			is_dead_rip(philo, actual_time);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex_meal);
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->mutex_meal);
	return (NULL);
}

static void	is_taking_fork(t_data *data, t_philo *philo)
{
	if (sem_wait(data->forks) == 0)
	{
		pthread_mutex_lock(&philo->mutex_states);
		philo->state = IS_TAKING_FORK;
		print_states(data, philo);
		pthread_mutex_unlock(&philo->mutex_states);
	}
	if (sem_wait(data->forks) == 0)
	{
		pthread_mutex_lock(&philo->mutex_states);
		philo->state = IS_TAKING_FORK;
		print_states(data, philo);
		pthread_mutex_unlock(&philo->mutex_states);
	}
}

static void	is_dead_rip(t_philo *philo, size_t actual_time)
{
	pthread_mutex_lock(&philo->mutex_states);
	philo->is_dead = true;
	philo->state = IS_DEAD;
	sem_wait(philo->data->print);
	printf("%s[%ld]%s philo n°%d %sdied%s\n", YELLOW, (actual_time
			- philo->data->start_time), NC, philo->id_philo, RED, NC);
	pthread_mutex_unlock(&philo->mutex_states);
	sem_post(philo->data->print);
	sem_post(philo->data->death);
}
