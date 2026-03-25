/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:38:44 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/25 22:30:00 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef enum s_states
{
	IS_TAKING_FORK,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}						t_states;

typedef struct s_data
{
	long				nb_philo;
	long				max_eat;
	pid_t				*p_id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	sem_t				*print;
	sem_t				*forks;
	sem_t				*death;
}						t_data;

typedef struct s_philo
{
	int					id_philo;
	size_t				last_meal;
	long				meals_counter;
	size_t				time;
	size_t				nbof_fork;
	pthread_t			thread;
	t_states			state;
}						t_philo;

// Utils
void					error_args(void);
void					ft_error(char *errorname);
long					ft_atol(const char *str);
size_t					get_time(void);
bool					check_str(const char *str);
void					*safe_calloc(size_t count, size_t size);

// Setup Cleanup
bool					setup_data(t_data *data, char **av, int ac);


// Routine
void	init_process(t_data *data, t_philo *philo);

#endif
