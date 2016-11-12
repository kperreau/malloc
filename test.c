#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int		main(void)
{
	char	*s = NULL;
	char	*s2 = NULL;

	write(1, "--START--\n", 10);

	for (int i=0; i<10; ++i)
	{
		s = malloc(1);
		strcpy(s, "a");
		//write(1, s, 3);
	}
	
	s2 = malloc(1);
	strcpy(s2, "e");
	write(1, s2, 1);
	
	write(1, s, 1);
	write(1, s2, 1);;
	
	return (0);
}
