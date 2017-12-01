/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 21:21:05 by asyed             #+#    #+#             */
/*   Updated: 2017/12/01 02:54:45 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

void	free_link_data(t_filelist *filelist)
{
	free(filelist->stbuf);
	filelist->stbuf = NULL;
	free(filelist->name);
	filelist->name = NULL;
}

int		add_stats(t_filelist *filelist, char *dirname)
{
	struct stat	*stbuf;
	int			size;

	stbuf = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (!stbuf)
	{
		printf("Failed to malloc(stbuf) %s\n", strerror(errno));
		return (-1);
	}
	if (lstat(build_path(filelist->path, filelist->name), stbuf) < 0)
	{
		printf("Error : %s (%s)\n", strerror(errno), build_path(filelist->path, filelist->name));
	}
	filelist->stbuf = stbuf;
	size = ft_nbrlen(filelist->stbuf->st_size);
	if (size > filelist->info->largest)
		filelist->info->largest = size;
	return (1);
}

char	*build_path(char *base, char *addition)
{
	if ((base && !*base) || !base)
		base = ft_strdup(addition);
		// base = ft_strjoin("./", addition);
	else
	{
		base = ft_strjoin(base, "/");
		base = ft_strjoin(base, addition);		
	}
	return (base);
}

int		add_file(t_filelist *filelist, char	*name, t_info *file_info, char *dirname)
{
	t_filelist *current_list;

	if (filelist->name)
	{
		current_list = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!current_list)
		{
			printf("Failed to malloc(newlink) %s\n", strerror(errno));
			return (0);
		}
		filelist->next = current_list;
	}
	else
		current_list = filelist;
	current_list->info = file_info;
	current_list->path = filelist->path;
	// current_list->path = build_path(current_list->path, dirname);
	current_list->name = ft_strdup(name);
	printf("{DEBUG} {3} File = %s (%s)\n", current_list->name, current_list->path);
	add_stats(current_list, dirname);
	return (1);
}