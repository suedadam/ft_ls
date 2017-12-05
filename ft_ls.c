/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:09:30 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 15:05:46 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** https://stackoverflow.com/questions/11736060/
** ..how-to-read-all-files-in-a-folder-using-c
*/

struct s_parse_options options[] = {
	{'r', &reverse},
	{'R', &recursive},
	{'l', &longlist},
	{'t', &modtime},
	{'a', &all}
};

void	printdata(t_filelist *filelist)
{
	struct passwd		*pwd;
	struct group		*grp;
	struct s_timespec	*time;

	ft_printf("total %d\n", CEILING_POS(*(filelist->totalblocks)));
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
		ft_printf("%c%s%3d %s  %s %*lld %s %2s %s %s\n",
			(S_ISDIR(filelist->stbuf->st_mode) ? 'd' : '-'),
			mode_parse(filelist->stbuf->st_mode),
			filelist->stbuf->st_nlink, pwd->pw_name, grp->gr_name,
			filelist->info->largest + 1, filelist->stbuf->st_size,
			time->month, time->date, time->time, filelist->name);
		filelist = filelist->next;
	}
}

int		ft_ls(t_info *file_info)
{
	struct dirent	*dir_info;
	DIR				*fd;
	t_filelist		*save;
	t_filelist		*filelist;

	if (!(fd = opendir(file_info->directory)))
		return ((ft_printf("Error: %s\n", strerror(errno))) ? -1 : -1);
	if (!init(&filelist))
		return (-1);
	save = filelist;
	filelist->path = build_path(filelist->path, file_info->directory);
	while ((dir_info = readdir(fd)) || closedir(fd))
	{
		if (hiddenfile(file_info, dir_info->d_name))
			continue ;
		filelist->info = file_info;
		add_file(&filelist, filelist, dir_info);
		if (filelist->next)
			filelist = filelist->next;
	}
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

int		main(int argc, char *argv[])
{
	struct s_info	*file_info;

	file_info = (t_info *)ft_memalloc(sizeof(t_info));
	if (!file_info)
	{
		ft_printf("Error: %s\n", strerror(errno));
		return (-1);
	}
	ls_parse_options(argv, argc, file_info);
	return (ft_ls(file_info));
}
