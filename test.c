#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int		main(void)
{
	char	*s = malloc(10);
	
	strcpy(s, "abc");
	write(1, s, strlen(s));
	return (0);
}
