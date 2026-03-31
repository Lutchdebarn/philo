/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:50:24 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/31 18:43:09 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	wait_all(t_data *data);
static void	*sem_death_checker(void *param);

void	init_process(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_create(&data->thread_main, NULL, sem_death_checker, data);
	while (i < data->nb_philo)
	{
		philo->id_philo = i + 1;
		pthread_mutex_lock(&data->mutex_pid);
		data->p_id[i] = fork();
		if (data->p_id[i] == -1)
			ft_error("fork() error\n");
		if (data->p_id[i] == 0)
		{
			free(data->p_id);
			start_routine(data, philo);
			close_sem(data);
			exit(0);
		}
		i++;
		pthread_mutex_unlock(&data->mutex_pid);
	}
	wait_all(data);
	pthread_join(data->thread_main, NULL);
}

void	print_states(t_data *data, t_philo *philo)
{
	size_t	current_time;
	size_t	final_time;

	current_time = get_time();
	final_time = current_time - data->start_time;
	sem_wait(data->print);
	if (philo->state == IS_TAKING_FORK)
		printf("[%ld] philo n°%d has taken a fork\n", final_time,
			philo->id_philo);
	else if (philo->state == IS_EATING)
		printf("[%ld] philo n°%d is eating\n", final_time, philo->id_philo);
	else if (philo->state == IS_SLEEPING)
		printf("[%ld] philo n°%d is sleeping\n", final_time, philo->id_philo);
	else if (philo->state == IS_THINKING)
		printf("[%ld] philo n°%d is thinking\n", final_time, philo->id_philo);
	sem_post(data->print);
	pthread_mutex_unlock(&philo->mutex_states);
}

static void	wait_all(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	sem_post(data->death);
}

static void	*sem_death_checker(void *param)
{
	t_data	*data;
	int		i;

	data = param;
	i = 0;
	if (!sem_wait(data->death))
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->mutex_pid);
			kill(data->p_id[i], SIGKILL);
			pthread_mutex_unlock(&data->mutex_pid);
			i++;
		}
	}
	return (NULL);
}

bool	check_eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	if (data->max_eat && philo->meals_counter >= data->max_eat)
	{
		pthread_mutex_unlock(&philo->mutex_meal);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex_meal);
		return (true);
	}
}
