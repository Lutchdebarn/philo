/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:30:06 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/27 09:39:17 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (sem_close(data->death) != 0)
		ft_error("sem_close() error\n");
	if (sem_close(data->forks) != 0)
		ft_error("sem_close() error\n");
	if (sem_close(data->waiter) != 0)
		ft_error("sem_close() error\n");
	if (sem_close(data->print) != 0)
		ft_error("sem_close() error\n");
	if (pthread_mutex_destroy(&philo->mutex_meal) != 0)
		ft_error("pthread_mutex_destroy() error\n");
	if (pthread_mutex_destroy(&philo->mutex_states) != 0)
		ft_error("pthread_mutex_destroy() error\n");
}
