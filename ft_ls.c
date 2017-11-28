/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:09:30 by asyed             #+#    #+#             */
/*   Updated: 2017/11/28 01:41:24 by asyed            ###   ########.fr       */
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

typedef struct	s_info
{
	struct stat		*stats;
}				t_info;

t_info	*fetch_info(struct dirent *dir_info)
{
	struct stat		*stbuf;
	struct s_info	*file_info;


	stbuf = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (!stbuf)
	{
		//Set errno;
		printf("Failed to malloc(stbuf) = \"%s\"\n", strerror(errno));
		return (NULL);
	}
	file_info = (t_info *)ft_memalloc(sizeof(t_info));
	if (!stbuf)
	{
		//Set errno;
		printf("Failed to malloc(file_info) = \"%s\"\n", strerror(errno));
		return (NULL);
	}
	lstat(dir_info->d_name, stbuf);
	file_info->stats = stbuf;
	return (file_info);
}

int		ft_ls(void)
{
	struct dirent	*dir_info;
	struct s_info	*file_info;
	DIR				*FD;

	if (!(FD = opendir("./")))
	{
		printf("Error! %s", strerror(errno));
		return (-1);
	}
	while ((dir_info = readdir(FD)))
	{
		if (!(file_info = fetch_info(dir_info)))
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

int		main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	// parse_options()
	return (ft_ls());
}