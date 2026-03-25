/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:46:15 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/25 22:02:07 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	memset(&data, 0, sizeof(t_data));
	if (ac == 5 || ac == 6)
	{
		if (setup_data(&data, av, ac))
		{
			init_process(&data, &philo);
		}
		else
			error_args();
	}
	else
		error_args();
}
