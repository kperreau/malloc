#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int		main(void)
{
	char	*s = malloc(10);
	char	*s2 = malloc(10);

	strcpy(s, "abc");
	write(1, s, 3);
	for (int i=0; i<1000000000; ++i)
	{	
		s = malloc(990);
		strcpy(s, "abc");
		//write(1, s, 3);
	}
	
	strcpy(s2, "efg");
	write(1, s2, 3);
	
	write(1, s, 3);
	write(1, s2, 3);;
	
	return (0);
}
