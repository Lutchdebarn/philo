/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:23:32 by ludebarn          #+#    #+#             */
/*   Updated: 2026/03/31 18:30:30 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_sleep(size_t ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
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
