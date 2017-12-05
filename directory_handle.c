/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:48:25 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 14:48:40 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	make_directory(t_filelist *filelist)
{
	t_filelist	*new;

	new = (t_filelist *)ft_memalloc(sizeof(t_filelist));
	if (!new)
	{
		ft_printf("Failed to malloc(tmpinfo) %s\n", strerror(errno));
		return ;
	}
	new->info = filelist->info;
	new->path = build_path(filelist->path, filelist->name);
	filelist->directory = new;
}

void	populate_directory(t_filelist *filelist)
{
	char			*tmp;
	struct dirent	*dir_info;
	DIR				*FD;
	t_filelist		*local;

	local = filelist->directory;
	if (!(FD = opendir(local->path)))
	{
		ft_printf("handle_directory(%s) Error (%s) %s\n", filelist->directory->path, filelist->name, strerror(errno));
		return ;
	}
	while ((dir_info = readdir(FD)))
	{
		add_file(&local, filelist, dir_info);
		if (local->next)
			local = local->next;
	}
	closedir(FD);
}

void	fetch_directories(t_filelist *filelist)
{
	char	*tmp;

	while (filelist)
	{
		if (ft_strcmp(filelist->name, ".") && ft_strcmp(filelist->name, "..") && S_ISDIR(filelist->stbuf->st_mode))
		{
			make_directory(filelist);
			populate_directory(filelist);
			sort_data(&(filelist->directory));
			ft_printf("\n%s/%s:\n", filelist->path, filelist->name);
			printdata(filelist->directory);
			fetch_directories(filelist->directory);
		}
		filelist = filelist->next;
	}
}
