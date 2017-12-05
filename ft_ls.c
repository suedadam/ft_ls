/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:09:30 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 01:46:02 by asyed            ###   ########.fr       */
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
	struct passwd *pwd;
	struct group *grp;

	printf("total %d\n", CEILING_POS(*(filelist->totalblocks)));
	while (filelist)
	{
		// printf("PRINTDATA(%s = %d)\n", filelist->name, hiddenfile(filelist->info, filelist->name));
		if (hiddenfile(filelist->info, filelist->name))
		{
			// printf("LOL: \"%s\" (%d %d)\n", filelist->name, ft_strcmp(filelist->name, "."), ft_strcmp(filelist->name, ".."));
			filelist = filelist->next;
			continue ;
		}
		// else
		// {
		// 	printf("wow adam: \"%s\" (%d %d)\n", filelist->name, ft_strcmp(filelist->name, "."), ft_strcmp(filelist->name, ".."));
		// }
		pwd = getpwuid(filelist->stbuf->st_uid);
		grp = getgrgid(filelist->stbuf->st_gid);
		// file mode, number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-month file was last modified, hour file last modified, minute file last modified, and the pathname
		printf("%s%3d %s  %s %*lld %s %d time %s\n", mode_parse(filelist->stbuf->st_mode), filelist->stbuf->st_nlink, pwd->pw_name, grp->gr_name, filelist->info->largest + 1, filelist->stbuf->st_size, "placeholder", 0, filelist->name);
		filelist = filelist->next;
	}
}

// void	handle_directory(t_filelist *filelist)
// {
// 	t_filelist		*tmpinfo;
// 	char			*tmp;
// 	struct dirent	*dir_info;
// 	DIR				*FD;

// 	tmpinfo = (t_filelist *)ft_memalloc(sizeof(t_filelist));
// 	if (!tmpinfo)
// 	{
// 		printf("Failed to malloc(tmpinfo) %s\n", strerror(errno));
// 		return ;
// 	}
// 	tmpinfo->path = filelist->path;
// 	filelist->directory = tmpinfo;
// 	// printf("handle_directory() %s\n", filelist->path);
// 	if (!(FD = opendir(tmpinfo->path)))
// 	{
// 		printf("handle_directory(%s) Error (%s) %s\n", tmpinfo->path, filelist->name, strerror(errno));
// 		return ;
// 	}
// 	while ((dir_info = readdir(FD)))
// 	{
// 		add_file(&tmpinfo, filelist, dir_info);
// 		// add_file(tmpinfo, dir_info->d_name, filelist->info, filelist->name);
// 		if (hiddenfile(tmpinfo->name) && S_ISDIR(tmpinfo->stbuf->st_mode))
// 		{
// 			tmp = ft_strdup(tmpinfo->path);
// 			tmpinfo->path = build_path(tmpinfo->path, tmpinfo->name);
// 			handle_directory(tmpinfo);
// 			printf("\n%s:\n", tmpinfo->path);
// 			sort_data(&(tmpinfo->directory));
// 			printdata(tmpinfo->directory);
// 			free(tmpinfo->path);
// 			tmpinfo->path = tmp;
// 		}
// 		if (tmpinfo->next)
// 			tmpinfo = tmpinfo->next;
// 	}
// 	closedir(FD);
// }

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
	// printf("New->path = \"%s\"\n", new->path);
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
		// printf("rofl\n");
		add_file(&local, filelist, dir_info);
		// printf("POS %s\n", filelist->directory->name);
		// if (hiddenfile(local->name) && S_ISDIR(local->stbuf->st_mode))
		// {
		// 	make_directory(local);
		// 	populate_directory(local);
		// 	printf("\n%s/%s:\n", local->path, local->name);
		// 	printdata(local->directory);
		// 	//Continue...
		// }
		if (local->next)
			local = local->next;
	}
	closedir(FD);
}

// void	fetch_directories(t_filelist *filelist)
// {
// 	char	*tmp;
// 	while (filelist)
// 	{
// 		if (ft_strcmp(filelist->name, ".") && ft_strcmp(filelist->name, "..") && S_ISDIR(filelist->stbuf->st_mode))
// 		{
// 			// tmp = ft_strdup(filelist->path);
// 			filelist->path = build_path(filelist->path, filelist->name);
// 			handle_directory(filelist);
// 			write(1, "1\n", 2);
// 			printf("\n(Penis) %s:\n", filelist->path);
// 			// free(filelist->path);
// 			// filelist->path = tmp;
// 			// sort_data(&(filelist->directory));
// 			printdata(filelist->directory);
// 		}
// 		filelist = filelist->next;
// 	}
// }

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
			// printf("(%s) filelist->directory->totalblocks = %p\n", filelist->name, filelist->directory->totalblocks);
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
		// printf("\"%s\" = %d\n", dir_info->d_name, hiddenfile(file_info, dir_info->d_name));
		if (hiddenfile(file_info, dir_info->d_name))
			continue ;
		// add_file(filelist, file_info, dir_info, file_info->directory);
		fixme_add_file(filelist, dir_info->d_name, file_info, file_info->directory);
		if (filelist->next)
			filelist = filelist->next;
	}
	closedir(FD);
	sort_data(&save);
	// printf("\n%s/%s:\n", save->path, save->name);
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