/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:03:47 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/18 17:22:42 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// (i + 1) % nb_philo = nb_philo % nb_philo = 0;  formule pour ne pas faire de depassement de memoire des fourchettes
// ./philo 5 800 200 200 [5]

int main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	memset(&data, 0, sizeof(t_data));
	if (ac == 5 || ac == 6)
	{
		if (setup_data(&data, av, ac))
		{
			setup_philo(&philo, &data);
		}
			// printf(" nb_philo = %ld\n time_to_die = %ld\n time_to_eat = %ld\n time_to_sleep = %ld\n max_eat = %ld\n", data.nb_philo, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.max_eat);
		else
			error_args();
	}
	else
		error_args();
	return (0);
}
