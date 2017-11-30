/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 21:21:05 by asyed             #+#    #+#             */
/*   Updated: 2017/11/30 15:09:20 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <errno.h>

int		add_stats(t_filelist *filelist)
{
	struct stat	*stbuf;
	int			size;

	stbuf = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (!stbuf)
	{
		printf("Failed to malloc(stbuf) %s\n", strerror(errno));
		return (-1);
	}
	lstat(filelist->name, stbuf);
	filelist->stbuf = stbuf;
	size = ft_nbrlen(filelist->stbuf->st_size);
	if (size > filelist->info->largest)
		filelist->info->largest = size;
	// printf("(%d) stbuf->st_blocks = %lld\n", filelist->info->totalblocks, stbuf->st_blocks);
	// filelist->info->totalblocks += stbuf->st_blocks;
	return (1);
}

int		add_file(t_filelist *filelist, char	*name, t_info *file_info)
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
	current_list->name = ft_strdup(name);
	add_stats(current_list);
	return (1);
}