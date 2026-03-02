#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
// microsecondes / 1000 = millisecondes
// secondes * 1000 = millisecondes

int main(void)
{
	time_t *titi;
	long long ms = 0;

	gettimeofday(titi, NULL);
	ms += titi
}
