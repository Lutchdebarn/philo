/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:50:24 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/25 22:41:45 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	start_routine(t_data *data, t_philo *philo);

void	init_process(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while(i < data->nb_philo)
	{
		data->p_id[i] = fork();
		if (data->p_id[i] == -1)
			ft_error("fork() error\n");
		if (data->p_id[i] == 0)
			start_routine(data, philo);
		i++;
	}
}

static void	start_routine(t_data *data, t_philo *philo)
{
	int	fork_count;

	fork_count = 0;
	while (1)
	{
		if (sem_wait(data->forks) == 0)
		{
			fork_count++;
			philo->state = IS_TAKING_FORK;
			sem_wait(data->print);
			printf("xxxx");
		}
		if (fork_count == 2)
		{
			philo->state = IS_DEAD;
		}
	}
}
