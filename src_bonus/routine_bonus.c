/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:50:24 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/26 11:24:47 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	start_routine(t_data *data, t_philo *philo);
void	print_states(t_data *data, t_philo *philo);
void	is_taking_fork(t_data *data, t_philo *philo);
void	*death_checker(void *param);
void	wait_all(t_data *data);
void	is_eating(t_data *data, t_philo *philo);
void	*sem_death_checker(void *param);

void	init_process(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_create(&data->thread_main, NULL, sem_death_checker, data);
	while(i < data->nb_philo)
	{
		philo->id_philo = i + 1;
		data->p_id[i] = fork();
		if (data->p_id[i] == -1)
			ft_error("fork() error\n");
		if (data->p_id[i] == 0)
			start_routine(data, philo);
		i++;
	}
	wait_all(data);
	pthread_join(data->thread_main, NULL);
}

static void	start_routine(t_data *data, t_philo *philo)
{

	pthread_create(&philo->thread, NULL, death_checker, philo);
	while (1)
	{
		if (data->max_eat)
			if (philo->meals_counter >= data->max_eat)
				break;
		is_taking_fork(data, philo);
		is_eating(data, philo);
		pthread_mutex_lock(&philo->mutex_states);
		philo->state = IS_SLEEPING;
		print_states(data, philo);
		pthread_mutex_unlock(&philo->mutex_states);
		usleep(data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->mutex_states);
		philo->state = IS_THINKING;
		pthread_mutex_unlock(&philo->mutex_states);
		if (data->time_to_eat * 2 > data->time_to_sleep)
			usleep(((data->time_to_eat * 2) - data->time_to_sleep)
				* 1000);
	}
	pthread_join(philo->thread, NULL);
	exit (EXIT_SUCCESS);
}

void	print_states(t_data *data, t_philo *philo)
{
	size_t	current_time;
	size_t	final_time;

	current_time = get_time();
	final_time = current_time - data->start_time;
	sem_wait(data->print);
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
	sem_post(data->print);
}
void	is_taking_fork(t_data *data, t_philo *philo)
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

void	is_eating(t_data *data, t_philo *philo)
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
	if(data->max_eat)
		philo->meals_counter++;
}

void	*death_checker(void *param)
{
	t_philo	*philo;
	size_t	actual_time;

	philo = param;
	while(1)
	{
		actual_time = get_time();
		pthread_mutex_lock(&philo->mutex_meal);
		if ((actual_time - philo->last_meal) > philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->mutex_meal);
			pthread_mutex_lock(&philo->mutex_states);
			philo->is_dead = true;
			philo->state = IS_DEAD;
			sem_wait(philo->data->print);
			printf("%s[%ld]%s philo n°%d %sdied%s\n", YELLOW, (actual_time -
				philo->data->start_time), NC, philo->id_philo, RED, NC);
			pthread_mutex_unlock(&philo->mutex_states);
			sem_post(philo->data->print);
			sem_post(philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex_meal);
		usleep(1000);
	}
	return (NULL);
}

void	wait_all(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while(i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	sem_post(data->death);
}

void	*sem_death_checker(void *param)
{
	t_data	*data;
	int		i;

	data = param;
	i = 0;
	if (!sem_wait(data->death))
	{
		while (i < data->nb_philo)
		{
			kill(data->p_id[i], SIGKILL);
			i++;
		}
	}
	return (NULL);
}
