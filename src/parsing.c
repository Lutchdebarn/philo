#include "philo.h"


// 1) Check  > INT_MAX
// 2) is number
// 3) timestamps > 60ms

bool	check_str(const char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (false);
	}
	if (i > 10)
		return (false);
	return (true);
}
