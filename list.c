/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 21:21:05 by asyed             #+#    #+#             */
/*   Updated: 2017/11/30 16:34:33 by asyed            ###   ########.fr       */
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
	printf("lstat(%s, %s) = %s\n", dirname, filelist->name, ft_strjoin(dirname, filelist->name));
	lstat(ft_strjoin(dirname, filelist->name), stbuf);
	filelist->stbuf = stbuf;
	size = ft_nbrlen(filelist->stbuf->st_size);
	if (size > filelist->info->largest)
		filelist->info->largest = size;
	// printf("(%d) stbuf->st_blocks = %lld\n", filelist->info->totalblocks, stbuf->st_blocks);
	// filelist->info->totalblocks += stbuf->st_blocks;
	return (1);
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
	current_list->path = ft_strjoin(ft_strjoin(current_list->path, dirname), name);
	// current_list->path = ft_strjoin(dirname, name);
	current_list->name = ft_strdup(name);
	// if (current_list->info->directory)
	// 	current_list->info->directory = ft_strjoin(current_list->info->directory, dirname);
	// else
	// 	current_list->info->directory = ft_strdup(dirname);
	add_stats(current_list, dirname);
	return (1);
}