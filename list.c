/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 21:21:05 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 14:10:40 by asyed            ###   ########.fr       */
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
		ft_printf("Failed to malloc(stbuf) %s\n", strerror(errno));
		return (-1);
	}
	if (lstat(build_path(filelist->path, filelist->name), stbuf) < 0)
	{
		ft_printf("Error : %s (%s)\n", strerror(errno), build_path(filelist->path, filelist->name));
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

int		add_file(t_filelist **filelist, t_filelist *file_info, struct dirent *dir_info)
{
	t_filelist	*current_list;

	// ft_printf("add_file() path = %s (%s)\n", (*filelist)->path, dir_info->d_name);
	if ((*filelist)->name)
	{
		current_list = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!current_list)
		{
			ft_printf("Failed to malloc(current_list) %s\n", strerror(errno));
			return (0);
		}
		(*filelist)->next = current_list;
		// ft_printf("(*filelist)->totalblocks = %p\n", (*filelist)->totalblocks);
		current_list->totalblocks = (*filelist)->totalblocks;
		current_list->path = (*filelist)->path;
		*filelist = (*filelist)->next;
		// ft_printf("add_file() {FLUFF} %s\n", dir_info->d_name);
	}
	else
	{
		// ft_printf("{BUN} %s\n", dir_info->d_name);
		current_list = (*filelist);
		free(current_list->totalblocks);
		current_list->totalblocks = (float *)ft_memalloc(sizeof(float));
		if (!current_list->totalblocks)
		{
			ft_printf("Failed to malloc(current_list->totalblocks) %s\n", strerror(errno));
			return (0);
		}
	}
	current_list->info = file_info->info;
	// ft_printf("Path = %s\n", (*filelist)->path);
	current_list->path = (*filelist)->path;
	current_list->name = ft_strdup(dir_info->d_name);
	// ft_printf("{BUN} %s == %s\n", current_list->name, dir_info->d_name);
	add_stats(current_list, file_info->name);
	// ft_printf("(%s) current_list->totalblocks = %p\n", current_list->name, current_list->totalblocks);
	// ft_printf("(%s) Previous = %f\n", current_list->name, *(current_list->totalblocks));
	if (!hiddenfile(file_info->info, current_list->name))
		*(current_list->totalblocks) += (float)current_list->stbuf->st_size / 512;
	// current_list->totalblocks += (hiddenfile(file_info->info, current_list->name)) ? 0 : (float)current_list->stbuf->st_size / 512;
	// ft_printf("(%s) New = %f\n", current_list->name, *(current_list->totalblocks));
	return (1);
}

int		fixme_add_file(t_filelist *filelist, char	*name, t_info *file_info, char *dirname)
{
	t_filelist *current_list;

	if (filelist->name)
	{
		current_list = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!current_list)
		{
			ft_printf("Failed to malloc(newlink) %s\n", strerror(errno));
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
			ft_printf("Failed to malloc(current_list->totalblocks) %s\n", strerror(errno));
			return (0);
		}
	}
	current_list->info = file_info;
	current_list->path = filelist->path;
	// current_list->path = build_path(current_list->path, dirname);
	current_list->name = ft_strdup(name);
	add_stats(current_list, dirname);
	*(current_list->totalblocks) += (float)current_list->stbuf->st_size / 512;
	return (1);
}