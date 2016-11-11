#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int		main(void)
{
	char	*s = malloc(10);
	char	*s2 = malloc(10);
	
	strcpy(s, "abc");
	puts(s);
	
	strcpy(s2, "efg");
	puts(s2);
	
	puts(s);
	puts(s2);
	return (0);
}
