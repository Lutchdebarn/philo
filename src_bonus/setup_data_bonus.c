/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:51:57 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/25 22:09:13 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_semaphore(t_data *data);

bool	setup_data(t_data *data, char **av, int ac)
{
	size_t	actual_time;

	actual_time = get_time();
	data->nb_philo = ft_atol(av[1]);
	if (data->nb_philo < 0 || data->nb_philo > INT_MAX)
		return (false);
	data->start_time = actual_time;
	data->time_to_die = ft_atol(av[2]);
	if (data->time_to_die > INT_MAX)
		return (false);
	data->time_to_eat = ft_atol(av[3]);
	if (data->time_to_eat > INT_MAX)
		return (false);
	data->time_to_sleep = ft_atol(av[4]);
	if (data->time_to_sleep > INT_MAX)
		return (false);
	if (ac == 6)
	{
		data->max_eat = ft_atol(av[5]);
		if (data->max_eat < 0 || data->max_eat > INT_MAX)
			return (false);
	}
	data->p_id = safe_calloc(data->nb_philo, sizeof(pid_t));
	init_semaphore(data);
	return (true);
}

static void	init_semaphore(t_data *data)
{
	sem_unlink("/table");
	data->forks = sem_open("/table", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
		ft_error("sem_open() error\n");
	sem_unlink("/death");
	data->death = sem_open("/death", O_CREAT, 0644, 0);
	if (data->death == SEM_FAILED)
		ft_error("sem_open() error\n");
	sem_unlink("/printf");
	data->print = sem_open("/printf", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		ft_error("sem_open() error\n");
}

size_t	get_time(void)
{
	struct timeval	time;
	size_t			current_time;

	memset(&time, 0, sizeof(struct timeval));
	if (gettimeofday(&time, NULL) < 0)
		ft_error("gettimeofday() error\n");
	current_time = time.tv_sec * 1000;
	current_time += time.tv_usec / 1000;
	return (current_time);
}
