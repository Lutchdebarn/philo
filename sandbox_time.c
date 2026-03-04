#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
// microsecondes / 1000 = millisecondes
// secondes * 1000 = millisecondes

int main(void)
{
	struct timeval temp_actuel;
	memset(&temp_actuel, 0, sizeof(struct timeval));

	size_t time_before = 0;
	size_t time_after = 0;
	int final_time = 0;

	gettimeofday(&temp_actuel, NULL);
	time_before = (temp_actuel.tv_usec / 1000);
	time_before += (temp_actuel.tv_sec * 1000);
	usleep(50000);
	memset(&temp_actuel, 0, sizeof(struct timeval));
	gettimeofday(&temp_actuel, NULL);
	time_after = (temp_actuel.tv_usec / 1000);
	time_after += (temp_actuel.tv_sec * 1000);
	final_time = (time_after - time_before);
	printf("Le temps de pause etais : %dms\n", final_time);
}
