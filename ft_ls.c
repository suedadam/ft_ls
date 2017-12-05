/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:09:30 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 03:39:00 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include "ft_printf.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>

/*
** https://stackoverflow.com/questions/11736060/how-to-read-all-files-in-a-folder-using-c
** 
*/

void	print_options(t_info *file_info)
{
	printf("======== Options ========\n");
	printf("all = %d\nlonglist = %d\nreverse = %d\nrecursive = %d\nmodtime = %d\n", file_info->all, file_info->longlist, file_info->reverse, file_info->recursive,file_info->modtime);
	printf("======== End ========\n");
}


struct s_parse_options options[] = {
	{'r', &reverse},
	{'R', &recursive},
	{'l', &longlist},
	{'t', &modtime},
	{'a', &all}
};

int		sanity(struct dirent *dir_info)
{
	if (!strcmp(dir_info->d_name, "."))
		return (0);
	if (!strcmp(dir_info->d_name, ".."))
		return (0);
	return (1);
}

int		init(t_filelist **filelist)
{
	if (filelist)
	{
		*filelist = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!filelist)
		{
			printf("Failed to malloc(filelist) %s\n", strerror(errno));
			return (0);
		}
		return (1);
	}
	else
		return (0);
}

int		hiddenfile(t_info *file_info, char *str)
{
	if (file_info->all)
		return (0);
	else if (*str == '.')
		return (1);
	else
		return (0);
}

void	printdata(t_filelist *filelist)
{
	struct passwd		*pwd;
	struct group		*grp;
	struct s_timespec	*time;

	printf("total %d\n", CEILING_POS(*(filelist->totalblocks)));
	while (filelist)
	{
		if (hiddenfile(filelist->info, filelist->name))
		{
			filelist = filelist->next;
			continue ;
		}
		pwd = getpwuid(filelist->stbuf->st_uid);
		grp = getgrgid(filelist->stbuf->st_gid);

		time = parse_time(ctime(&(filelist->stbuf->st_mtime)));
		// file mode, number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-month file was last modified, hour file last modified, minute file last modified, and the pathname
		printf("%s%3d %s  %s %*lld %s %2s %s %s\n", mode_parse(filelist->stbuf->st_mode), filelist->stbuf->st_nlink, pwd->pw_name, grp->gr_name, filelist->info->largest + 1, filelist->stbuf->st_size, time->month, time->date, time->time, filelist->name);
		filelist = filelist->next;
	}
}

void	make_directory(t_filelist *filelist)
{
	t_filelist	*new;

	new = (t_filelist *)ft_memalloc(sizeof(t_filelist));
	if (!new)
	{
		printf("Failed to malloc(tmpinfo) %s\n", strerror(errno));
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
		printf("handle_directory(%s) Error (%s) %s\n", filelist->directory->path, filelist->name, strerror(errno));
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
			printf("\n%s/%s:\n", filelist->path, filelist->name);
			printdata(filelist->directory);
			fetch_directories(filelist->directory);
		}
		filelist = filelist->next;
	}
}

void	sort_data(t_filelist **filelist)
{
	if ((*filelist)->info->modtime)
		*filelist = time_sort(*filelist);
	else if ((*filelist)->info->reverse)
		*filelist = reverse_sort(*filelist);
	else
		*filelist = alpha_sort(*filelist);
}

int		ft_ls(t_info *file_info)
{
	struct dirent	*dir_info;
	DIR				*FD;
	t_filelist		*save;
	t_filelist		*filelist;

	if (!(FD = opendir(file_info->directory)))
	{
		printf("Error! (%s) %s\n", file_info->directory, strerror(errno));
		return (-1);
	}
	print_options(file_info);
	if (!init(&filelist))
		return (-1);
	save = filelist;
	filelist->path = build_path(filelist->path, file_info->directory);
	while ((dir_info = readdir(FD)))
	{
		if (hiddenfile(file_info, dir_info->d_name))
			continue ;
		fixme_add_file(filelist, dir_info->d_name, file_info, file_info->directory);
		if (filelist->next)
			filelist = filelist->next;
	}
	closedir(FD);
	sort_data(&save);
	printdata(save);
	if (filelist->info->recursive)
		fetch_directories(save);
	return (1);
}

int		itterate_search(t_info *file_info, char *str)
{
	int	i;
	int ret;

	i = 0;
	ret = 0;
	while (options[i].flag && *str)
	{
		if (*str == options[i].flag)
		{
			ret += options[i].func(file_info);
			i = 0;
			str++;
		}
		i++;
	}
	return (ret);
}

void	ls_parse_options(char *argv[], int argc, t_info *file_info)
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
			break;
		i++;
	}
	if (i < argc)
		file_info->directory = ft_strdup(argv[i]);
	else
		file_info->directory = ft_strdup("./");
}

int		main(int argc, char *argv[])
{
	struct s_info	*file_info;

	file_info = (t_info *)ft_memalloc(sizeof(t_info));
	if (!file_info)
	{
		//Errno;
		printf("Failed to malloc(file_info) = %s\n", strerror(errno));
		return (-1);
	}
	ls_parse_options(argv, argc, file_info);;
	return (ft_ls(file_info));
}