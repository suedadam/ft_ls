/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 03:35:39 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 03:37:44 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>
#include <stdlib.h>

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