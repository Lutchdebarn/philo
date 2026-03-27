/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:38:44 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/27 09:43:29 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define NC "\e[0m"

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
	pthread_t			thread_main;
	pid_t				*p_id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	sem_t				*print;
	sem_t				*forks;
	sem_t				*death;
	sem_t				*waiter;
}						t_data;

typedef struct s_philo
{
	int					id_philo;
	size_t				last_meal;
	long				meals_counter;
	bool				is_dead;
	size_t				time;
	pthread_t			thread;
	pthread_mutex_t		mutex_meal;
	pthread_mutex_t		mutex_states;
	t_states			state;
	t_data				*data;
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
void					setup_philo(t_data *data, t_philo *philo);
void					close_prog(t_data *data, t_philo *philo);

// Routine
void					init_process(t_data *data, t_philo *philo);
void					print_states(t_data *data, t_philo *philo);
void					start_routine(t_data *data, t_philo *philo);

#endif
