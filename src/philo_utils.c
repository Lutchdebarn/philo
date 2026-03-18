#include "philo.h"

long	ft_atol(const char *str)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (!check_str(str))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	return (nb * sign);
}

void	error_args(void)
{
	printf("Error usage type :\n\t\t <number_of_philosophers time_to_die");
	printf(" time_to_eat time_to_sleep [number_of_times_each_philosopher");
	printf("_must_eat]>\n");
	exit (EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (!ret)
	{
		write(2, "Error with malloc\n", 19);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

void	ft_error(char *errorname)
{
	printf("%s\n", errorname);
	exit(EXIT_FAILURE);
}
