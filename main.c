#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	char *s = malloc(15);
	
	s = realloc(s, 50);
	s = realloc(s, 12);
	strcpy(s, "abcdefghijkl");
	puts(s);
	free(s);
	return(0);
}
