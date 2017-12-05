/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 21:21:05 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 14:45:08 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		ft_printf("Error: %s\n", strerror(errno));
		return (-1);
	}
	if (lstat(build_path(filelist->path, filelist->name), stbuf) < 0)
	{
		ft_printf("Error: %s\n", strerror(errno));
		return (-1);
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
	else
	{
		base = ft_strjoin(base, "/");
		base = ft_strjoin(base, addition);
	}
	return (base);
}

int		copy_info(t_filelist **filelist, t_filelist *current_list,
				t_filelist *file_info, struct dirent *dir_info)
{
	current_list->info = file_info->info;
	current_list->path = (*filelist)->path;
	current_list->name = ft_strdup(dir_info->d_name);
	if (add_stats(current_list, file_info->name) > 0)
	{
		if (!hiddenfile(file_info->info, current_list->name))
			*(current_list->totalblocks) +=
			(float)current_list->stbuf->st_size / 512;
		return (1);
	}
	else
		return (0);
}

int		add_file(t_filelist **filelist, t_filelist *file_info,
				struct dirent *dir_info)
{
	t_filelist	*current_list;

	if ((*filelist)->name)
	{
		current_list = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!current_list)
		{
			ft_printf("Error: %s\n", strerror(errno));
			return (0);
		}
		(*filelist)->next = current_list;
		current_list->totalblocks = (*filelist)->totalblocks;
		current_list->path = (*filelist)->path;
		*filelist = (*filelist)->next;
	}
	else
	{
		current_list = (*filelist);
		free(current_list->totalblocks);
		current_list->totalblocks = (float *)ft_memalloc(sizeof(float));
		if (!current_list->totalblocks)
			return ((ft_printf("Error: %s\n", strerror(errno)) ? 0 : 0));
	}
	return (copy_info(filelist, current_list, file_info, dir_info));
}

int		fixme_add_file(t_filelist *filelist, char *name, t_info *file_info,
						char *dirname)
{
	t_filelist *current_list;

	if (filelist->name)
	{
		current_list = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!current_list)
		{
			ft_printf("Error: %s\n", strerror(errno));
			return (0);
		}
		current_list->totalblocks = filelist->totalblocks;
		filelist->next = current_list;
	}
	else
	{
		current_list = filelist;
		free(current_list->totalblocks);
		current_list->totalblocks = (float *)ft_memalloc(sizeof(float));
		if (!current_list->totalblocks)
		{
			ft_printf("Error: %s\n", strerror(errno));
			return (0);
		}
	}
	current_list->info = file_info;
	current_list->path = filelist->path;
	current_list->name = ft_strdup(name);
	add_stats(current_list, dirname);
	*(current_list->totalblocks) += (float)current_list->stbuf->st_size / 512;
	return (1);
}
