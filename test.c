#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define NB 50000

int		main(void)
{
	char	*s = NULL;
	char	*s2 = NULL;
	char	*t[NB];

	write(1, "--START--\n", 10);

	for (int i=0; i < 100000; ++i)
	{
		s = malloc(10);
		strcpy(s, "12345678\n");
		// write(1, s, 10);
		free(s);
	}
	
	malloc(152000);
	malloc(1);
	malloc(1);
	malloc(1);
	
	malloc(700);
	malloc(50000000);
	
	for (int i=0; i < NB; ++i)
	{
		t[i] = malloc(5730);
		strcpy(t[i], "12345678\n");
	}
	
	s = malloc(1000000);
	
	
	strcpy(s, "12345678\n");
	write(1, s, 10);
	free(s);
	
	for (int i=0; i < NB; ++i)
	{
		malloc(1);
		free(malloc(1250));
		free(t[i]);
	}
	
	// s2 = malloc(10);
	// strcpy(s2, "edf\n");
	// write(1, s2, 4);
	
	// write(1, s, 1);
	// write(1, s2, 1);;
	
	return (0);
}