#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

void		*func1(void *data)
{
	int i;
	char *s = malloc(600);
	for (i = 0; i < 600; ++i)
		s[i] = 'a';
	s[i] = 0;
	//puts(s);
	return (data);
}

void		*func2(void *data)
{
	int i;
	char *s = malloc(900);
	for (i = 0; i < 900; ++i)
		s[i] = 'b';
	s[i] = 0;
	//puts(s);
	return (data);
}

void		*func3(void *data)
{
	int i;
	char *s = malloc(700);
	for (i = 0; i < 700; ++i)
		s[i] = 'c';
	s[i] = 0;
	//puts(s);
	return (data);
}

void		*func4(void *data)
{
	int i;
	char *s = malloc(820);
	for (i = 0; i < 820; ++i)
		s[i] = 'd';
	s[i] = 0;
	//puts(s);
	return (data);
}

int		main(void)
{	
	pthread_t	thread[4];
	void		*data;

	data = malloc(10);
	for (size_t i = 0; i < 50000; ++i)
	{
		pthread_create(&thread[0], NULL, func1, data);
		pthread_create(&thread[1], NULL, func2, data);
		pthread_create(&thread[2], NULL, func3, data);
		pthread_create(&thread[3], NULL, func4, data);
		//pthread_join(thread[0], NULL);
		//pthread_join(thread[1], NULL);
	}
	return (0);
}
