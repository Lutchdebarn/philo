/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:56:06 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/25 20:17:25 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex(t_data *data);

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	destroy_mutex(data);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&data->philos[i].protect_meal) != 0)
			ft_error("Destroy mutex failed\n");
		i++;
	}
	free(data->fork);
	free(data->philos);
}

static void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->simul) != 0)
		ft_error("Destroy mutex failed\n");
	if (pthread_mutex_destroy(&data->is_talking) != 0)
		ft_error("Destroy mutex failed\n");
	if (pthread_mutex_destroy(&data->mutex_state) != 0)
		ft_error("Destroy mutex failed\n");
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]) == 0)
			i++;
		else
			ft_error("Destroy mutex failed\n");
	}
}
