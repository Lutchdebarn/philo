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

# define YELLOW "\e[1;33m"

typedef struct s_data t_data;
typedef struct s_philo t_philo;

typedef enum	s_states
{
	IS_TAKING_FORK,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}				t_states;

typedef struct	s_data
{
	long		nb_philo;
	long		max_eat;
	bool		is_running;
	pthread_t	monitor;
	pthread_mutex_t	simul;
	pthread_mutex_t	*fork;
	pthread_mutex_t	is_talking;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	t_philo			*philos;
}			t_data;

typedef struct s_philo
{
	int		id_philo;
	pthread_t	ID;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	protect_meal;
	size_t		last_meal;
	long		meals_counter;
	size_t		time;
	t_states	state;
	t_data		*data;
}				t_philo;

// Routine fonctions
void	creat_thread(t_data *data);
void	print_states(t_philo *philo);

// Utils
void	error_args(void);
void	ft_error(char *errorname);
long	ft_atol(const char *str);
bool	check_str(const char *str);
void	*safe_calloc(size_t count, size_t size);

// Setup
bool	setup_data(t_data *data, char **av, int ac);
void	setup_philo(t_data *data);

#endif
