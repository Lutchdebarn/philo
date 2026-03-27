/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:50:24 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/27 09:27:55 by lucasdebarn      ###   ########.fr       */
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

static void	wait_all(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			i++;
		else
			break ;
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
			kill(data->p_id[i], SIGKILL);
			i++;
		}
	}
	return (NULL);
}
