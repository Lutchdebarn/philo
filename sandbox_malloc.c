# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>

# define NC "\e[0m"
# define YELLOW "\e[1;33m"

void	*thread_routine(void *data)
{
	pthread_t tid;

	tid = pthread_self();

	printf("%sThread [%ld]: le plus grand ennui c'est d'exister sans vitre.%s\n", YELLOW, tid, NC);
	return (NULL);
}

int main(void)
{
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1, NULL, thread_routine, NULL);
	printf("Main: Creation du premier thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, NULL);
	printf("Main: Creation du second thread [%ld]\n", tid2);
	pthread_join(tid1, NULL);
	printf("Main: Union du premier thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Union du second thread [%ld]\n", tid2);
	return (0);
}
