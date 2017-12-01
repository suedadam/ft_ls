/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:09:30 by asyed             #+#    #+#             */
/*   Updated: 2017/12/01 02:38:42 by asyed            ###   ########.fr       */
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

// int		fetch_info(struct dirent *dir_info, t_info *file_info)
// {
// 	struct stat		*stbuf;

// 	stbuf = (struct stat *)ft_memalloc(sizeof(struct stat));
// 	if (!stbuf)
// 	{
// 		//Set errno;
// 		printf("Failed to malloc(stbuf) = \"%s\"\n", strerror(errno));
// 		return (0);
// 	}
// 	lstat(dir_info->d_name, stbuf);
// 	file_info->stats = stbuf;
// 	return (1);
// }

int		sanity(struct dirent *dir_info)
{
	if (!strcmp(dir_info->d_name, "."))
		return (0);
	if (!strcmp(dir_info->d_name, ".."))
		return (0);
	return (1);
}

// void	print_files(t_info *file_info, DIR *FD)
// {
// 	struct dirent	*new_info;

// 	while ((new_info = readdir(FD)))
// 	{
// 		if (!fetch_info(new_info, file_info))
// 		{
// 			printf("Failed to fetch file info\n");
// 			return ;
// 		}
// 	}
// }

// void	handle_directory(t_info *file_info, struct dirent *dir_info)
// {
// 	DIR				*FD;
// 	struct dirent	*new_info;

// 	if (sanity(dir_info))
// 		ft_printf("%s\n", dir_info->d_name);
// 	if (!(FD = opendir(dir_info->d_name)))
// 	{
// 		printf("Error bitch %s\n", strerror(errno));
// 		return ;
// 	}
// 	print_files(file_info, FD);
// 	while ((new_info = readdir(FD)))
// 	{
// 		if (!fetch_info(new_info, dir_info))
// 		{
// 			printf("Failed to fetch file info\n");
// 			return ;
// 		}
// 		if (S_ISDIR(file_info->stats->st_mode) && sanity(new_info))
// 		{

// 		}
// 	}
// }

// void	handle_directory(t_info *file_info, struct dirent *dir_info)
// {
// 	DIR				*FD;
// 	struct dirent	*new_info;
// 	t_info 			*tmp_info;

// 	if (sanity(dir_info))
// 		ft_printf("%s\n", dir_info->d_name);
// 	if (!(FD = opendir(dir_info->d_name)))
// 	{
// 		printf("Error bitch %s\n", strerror(errno));
// 		return ;
// 	}
// 	tmp_info = (t_info *)ft_memalloc(sizeof(t_info));
// 	if (!tmp_info)
// 	{
// 		printf("Errno = %s\n", strerror(errno));
// 		return ;
// 	}
// 	while ((new_info = readdir(FD)))
// 	{
// 		if (!fetch_info(new_info, tmp_info))
// 		{
// 			//Set errno accordingly.
// 			printf("Failed to fetch file's info\n");
// 			return ;
// 		}
// 		if (file_info->recursive)
// 		{

// 			if (S_ISDIR(file_info->stats->st_mode) && sanity(new_info))
// 			{
// 				printf("Directory name: %s\n", new_info->d_name);
// 				handle_directory(file_info, new_info);
// 			}
// 		}
// 		// ft_printf("%s\n", new_info->d_name);
// 	}
// }

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

int		hiddenfile(char *str)
{
	return (ft_strcmp(str, ".") && ft_strcmp(str, ".."));
}

void	printdata(t_filelist *filelist)
{
	struct passwd *pwd;
	struct group *grp;

	// printf("total %d\n", total_512(filelist));
	while (filelist && filelist->name)
	{
		if (!filelist->info->all && !ft_strncmp(filelist->name, ".", 1))
		{
			filelist = filelist->next;
			continue ;
		}
		pwd = getpwuid(filelist->stbuf->st_uid);
		grp = getgrgid(filelist->stbuf->st_gid);
		// file mode, number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-month file was last modified, hour file last modified, minute file last modified, and the pathname
		printf("%s%3d %s  %s %*lld %s %d time %s\n", mode_parse(filelist->stbuf->st_mode), filelist->stbuf->st_nlink, pwd->pw_name, grp->gr_name, filelist->info->largest + 1, filelist->stbuf->st_size, "placeholder", 0, filelist->name);
		filelist = filelist->next;
	}
}

void	handle_directory(t_filelist *filelist)
{
	t_filelist		*tmpinfo;
	char			*tmp;
	struct dirent	*dir_info;
	DIR				*FD;

	tmpinfo = (t_filelist *)ft_memalloc(sizeof(t_filelist));
	if (!tmpinfo)
	{
		printf("Failed to malloc(tmpinfo) %s\n", strerror(errno));
		return ;
	}
	tmpinfo->path = filelist->path;
	filelist->directory = tmpinfo;
	// printf("handle_directory() %s\n", filelist->path);
	if (!(FD = opendir(filelist->path)))
	{
		printf("handle_directory(%s) Error (%s) %s\n", filelist->path, filelist->name, strerror(errno));
		return ;
	}
	while ((dir_info = readdir(FD)))
	{
		// printf("handle_directory() Current path = %s + %s\n", tmpinfo->path, filelist->name);
		add_file(tmpinfo, dir_info->d_name, filelist->info, filelist->name);
		printf("{DEBUG} %s (%d %d) (\"%s\")\n", tmpinfo->name, hiddenfile(tmpinfo->name), S_ISDIR(tmpinfo->stbuf->st_mode), tmpinfo->path);
		if (hiddenfile(tmpinfo->name) && S_ISDIR(tmpinfo->stbuf->st_mode))
		{
			// tmp = ft_strdup(tmpinfo->path);
			tmpinfo->path = build_path(tmpinfo->path, tmpinfo->name);
			handle_directory(tmpinfo);
			printf("\n%s:\n", tmpinfo->path);
			printdata(tmpinfo->directory);
			// free(tmpinfo->path);
			// tmpinfo->path = tmp;
		}
		if (tmpinfo->next)
			tmpinfo = tmpinfo->next;
	}
	closedir(FD);
}

char	*make_dir_format(char *str)
{
	char *new;
	int i;
	int length;

	length = ft_strlen(str);
	i = 0;
	new = (char *)ft_memalloc(length + 3 * sizeof(char));
	if (!new)
	{
		printf("Error malloc(%s)\n", strerror(errno));
		return (NULL);
	}
	printf("before: %s\n", str);
	new[i++] = '.';
	new[i++] = '/';
	ft_strcat(new, str);
	i += length;
	printf("After: %s\n", new);
	new[i] = '/';
	return (new);
}

void	fetch_directories(t_filelist *filelist)
{
	char	*tmp;
	while (filelist)
	{
		printf("{DEBUG} Path = %s\n", filelist->path);
		if (ft_strcmp(filelist->name, ".") && ft_strcmp(filelist->name, "..") && S_ISDIR(filelist->stbuf->st_mode))
		{
			printf("{DEBUG} {2} What a fucking piece of shit: %s\n", filelist->name);
			// tmp = ft_strdup(filelist->path);
			filelist->path = build_path(filelist->path, filelist->name);
			printf("{DEBUG} fetch_directories() = %s\n", filelist->path);
			handle_directory(filelist);
			printf("\n%s:\n", filelist->path);
			// free(filelist->path);
			// filelist->path = tmp;
			printdata(filelist->directory);
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
		add_file(filelist, dir_info->d_name, file_info, file_info->directory);
		if (filelist->next)
			filelist = filelist->next;
	}
	closedir(FD);
	if (filelist->info->recursive)
	{
		printf("{DEBUG} {2} Called bitch\n");
		fetch_directories(save);
	}
	sort_data(&save);
	printf("\n=======Normal list info ======\n");
	printdata(save);
	return (1);
}

int		itterate_search(t_info *file_info, char *str)
{
	int	i;
	int ret;

	i = 0;
	ret = 0;
	while (options[i].flag)
	{
		if (*str == options[i].flag)
		{
			ret += options[i].func(file_info);
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
	// if (argc > 3)
		ls_parse_options(argv, argc, file_info);
	printf("Total %d\n", file_info->totalblocks);
	// printf("Directory: %s\n", file_info->directory);
	return (ft_ls(file_info));
}