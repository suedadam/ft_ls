/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 03:35:39 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 14:59:05 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_timespec	*parse_time(char *str)
{
	char		**data;
	t_timespec	*new;

	new = (t_timespec *)ft_memalloc(sizeof(t_timespec));
	if (!new)
	{
		ft_printf("failed to ft_memalloc(t_timespec) %s\n", strerror(errno));
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

int			hiddenfile(t_info *file_info, char *str)
{
	if (file_info->all)
		return (0);
	else if (*str == '.')
		return (1);
	else
		return (0);
}

int			init(t_filelist **filelist)
{
	if (filelist)
	{
		*filelist = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!filelist)
		{
			ft_printf("Failed to malloc(filelist) %s\n", strerror(errno));
			return (0);
		}
		return (1);
	}
	else
		return (0);
}

void		ls_parse_options(char *argv[], int argc, t_info *file_info)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (*(argv[i]) == '-')
		{
			(argv[i])++;
			itterate_search(file_info, argv[i]);
		}
		else
			break ;
		i++;
	}
	if (i < argc)
		file_info->directory = ft_strdup(argv[i]);
	else
		file_info->directory = ft_strdup("./");
}
