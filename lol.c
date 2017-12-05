#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "libft.h"

typedef struct	s_timespec
{
	char		*month;
	char		*time;
	char		*date;
}				t_timespec;

t_timespec	*parse_time(char *str)
{
	char **data;
	t_timespec *new;

	new = (t_timespec *)ft_memalloc(sizeof(t_timespec));
	if (!new)
	{
		printf("failed to ft_memalloc(t_timespec) %s\n", strerror(errno));
		return (NULL);
	}
	data = ft_strsplit(str, ' ');
	new->month = ft_strdup(data[1]);
	data[3][ft_strlen(data[3]) - 3] = '\0';
	new->time = ft_strdup(data[3]);
	new->date = ft_strdup(data[2]);
	while (*data)
		free(*data++);
	return (new);
}

int
main(void)
{
	time_t rawtime;
	struct s_timespec *LOL;

	time (&rawtime);
	LOL = calloc(sizeof(t_timespec), 1);
	LOL = parse_time(ctime(&rawtime));
	printf("(%s) %s\n", LOL->month, ctime(&rawtime));
}