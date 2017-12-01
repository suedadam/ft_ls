#include <stdlib.h>
#include <stdio.h>

int		hiddenfile(char *str)
{
	return (ft_strcmp(str, ".") && ft_strcmp(str, ".."));
}

int
main(void)
{
	if (hiddenfile("Contents"))
		printf("pass\n");
	else
		printf("fail\n");
}