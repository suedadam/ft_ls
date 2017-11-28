/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:09:30 by asyed             #+#    #+#             */
/*   Updated: 2017/11/28 02:59:08 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

int		fetch_info(struct dirent *dir_info, t_info *file_info)
{
	struct stat		*stbuf;

	stbuf = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (!stbuf)
	{
		//Set errno;
		printf("Failed to malloc(stbuf) = \"%s\"\n", strerror(errno));
		return (0);
	}
	lstat(dir_info->d_name, stbuf);
	file_info->stats = stbuf;
	return (1);
}

int		ft_ls(t_info *file_info)
{
	struct dirent	*dir_info;
	DIR				*FD;

	if (!(FD = opendir("./")))
	{
		printf("Error! %s", strerror(errno));
		return (-1);
	}
	print_options(file_info);
	while ((dir_info = readdir(FD)))
	{
		if (!fetch_info(dir_info, file_info))
		{
			//Set errno accordingly.
			printf("Failed to fetch file's info\n");
			return (-1);
		}
		if (S_ISDIR(file_info->stats->st_mode))
			printf("(Directory)");
		// if (dir_info->d_type == DT_UNKNOWN)
		// 	printf("(Unknown)\n");
		printf("%s ", dir_info->d_name);
	}
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

void	parse_options(char *argv[], int argc, t_info *file_info)
{
	char	*str;
	int		i;

	i = 1;
	while (i < argc)
	{
		str = argv[i];
		if (*str == '-')
		{
			str++;
			itterate_search(file_info, str);
		}
		i++;
	}
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
		parse_options(argv, argc, file_info);
	return (ft_ls(file_info));
}