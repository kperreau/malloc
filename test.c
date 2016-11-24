#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define NB 50000

void	ft_putnbr(long n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = 48 + n;
		write(1, &c, 1);
	}
}

int		main(void)
{
	char	*s = NULL;
	char	*s2 = NULL;
	char	*t[NB];

	write(1, "--START--\n", 10);

	
	
	for (int i=0; i < 10000; ++i)
	{
		// ft_putnbr(i);
		// write(1, "\n", 1);
		s = malloc(1000);
		s = realloc(s, 10);
		malloc(10);
		// free(s);
		s = realloc(s, 50);
		s2 = malloc(100);
		s2 = realloc(s2, 500);
		malloc(10);
		
		
		strcpy(s2, "12345678\n");
		for (int j=0; j < 500; ++j)
			s2[j] = 'a';
		// write(1, s, 10);
		free(s2);
		// free(s);
	}
	
	// s2 = malloc(10);
	// strcpy(s2, "edf\n");
	// write(1, s2, 4);
	
	// write(1, s, 1);
	// write(1, s2, 1);;
	
	return (0);
}