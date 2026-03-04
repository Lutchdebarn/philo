#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>

typedef enum	s_states
{
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}				t_states;

typedef struct	s_data
{
	int		nb_philo;
	int		max_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	is_talking;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}			t_data;

typedef struct s_philo
{
	int		id_philo;
	pthread_t	ID;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	size_t		last_meal;
	size_t		time;
	t_states	state;
	t_data		*data;
}				t_philo;

#endif
