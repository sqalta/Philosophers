# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

/*
void* routine()
{
	struct timeval time1;
	struct timeval time;
	time_t timelas;
	gettimeofday(&time, NULL);
	while (1)
	{
		printf ("First Try\n");
		gettimeofday(&time1, NULL);
		timelas = time1.tv_sec - time.tv_sec;
		printf ("zaman :%ld \n", timelas);
		char q = getchar();
		if (q  == 'q')
			exit(1);
		sleep(2);
	}
}
*/
int up = 1;
int down = 5;
pthread_mutex_t mut1;
pthread_mutex_t mut2;

void *increment(void *mutex)
{
	int *mutex1 = (int *)mutex;
	if (mutex1 == &up)
	{
		pthread_mutex_lock(&mut1);
		mutex++;
	}
	pthread_mutex_unlock(&mut1);
	return (NULL);
}

void *decrease(void *mutex)
{
	printf ("%d\n", *(int *)mutex);
	getchar();
	int *mutex2 = (int *)mutex;
	if (mutex2 == &down)
	{
		pthread_mutex_lock(&mut2);
		printf ("%d\n", *(int *)mutex);
		*(int *)mutex++;
		printf ("%d\n", *(int *)mutex);
		getchar();
	}
	pthread_mutex_unlock(&mut2);
	return (NULL);
}
int main ()
{
	pthread_t th;
	pthread_t th1;
	pthread_mutex_t mut1;
	pthread_mutex_t mut2;
	pthread_create(&th, NULL, increment, &up);
	pthread_create(&th1, NULL, decrease, &down);
	pthread_join(th, NULL);
	pthread_join(th1, NULL);
	printf ("%d\n", up);
	printf ("%d\n", down);
}