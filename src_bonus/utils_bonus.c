/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:30:06 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/31 18:32:04 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_mutex(t_philo *philo);

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

void	close_prog(t_data *data, t_philo *philo)
{
	if (data->p_id)
		free(data->p_id);
	close_mutex(philo);
	close_sem(data);
	if (sem_unlink("/death") < 0)
		ft_error("sem_unlink() error\n");
	if (sem_unlink("/table") < 0)
		ft_error("sem_unlink() error\n");
	if (sem_unlink("/waiter") < 0)
		ft_error("sem_unlink() error\n");
	if (sem_unlink("/printf") < 0)
		ft_error("sem_unlink() error\n");
}

static void	close_mutex(t_philo *philo)
{
	if (pthread_mutex_destroy(&philo->mutex_meal) != 0)
		ft_error("pthread_mutex_destroy() error\n");
	if (pthread_mutex_destroy(&philo->mutex_states) != 0)
		ft_error("pthread_mutex_destroy() error\n");
}

void	close_sem(t_data *data)
{
	if (sem_close(data->death) != 0)
		ft_error("sem_close() error\n");
	if (sem_close(data->forks) != 0)
		ft_error("sem_close() error\n");
	if (sem_close(data->waiter) != 0)
		ft_error("sem_close() error\n");
	if (sem_close(data->print) != 0)
		ft_error("sem_close() error\n");
}

void	precise_sleep(size_t ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}
