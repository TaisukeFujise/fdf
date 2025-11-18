#include <sys/time.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%ld, %06lu\n", tv.tv_sec, tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%ld, %06lu\n", tv.tv_sec, tv.tv_usec);
	return (0);
}
