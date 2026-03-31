/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:46:15 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/31 18:06:03 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	memset(&data, 0, sizeof(t_data));
	if (ac == 5 || ac == 6)
	{
		if (setup_data(&data, av, ac))
		{
			setup_mutex_and_philo(&data, &philo);
			init_process(&data, &philo);
			close_prog(&data, &philo);
		}
		else
			error_args();
	}
	else
		error_args();
}
