#include <stdio.h>
#include <stdlib.h>
#include <float.h>
int N;
int max=1000;
int main(int argc, const char *argv[])
{
	int i;
	sscanf(argv[1],"%d", &N);
	for(i=0;i<N;i++){
		printf("%f %f\n", ((double)(rand())/RAND_MAX)*max, ((double)(rand())/RAND_MAX)*max);
	}
	return 0;
}
