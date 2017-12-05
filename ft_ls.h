/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:13:02 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 14:57:36 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <grp.h>
# include <pwd.h>

/*
** https://www.linuxquestions.org/questions/programming-9/
** ..ceiling-function-c-programming-637404/
*/

# define CEILING_POS(X) ((X-(int)(X)) > 0 ? (int)(X+1) : (int)(X))

typedef struct	s_timespec
{
	char		*month;
	char		*time;
	char		*date;
}				t_timespec;

typedef struct	s_info
{
	uint8_t		all:1;
	uint8_t		longlist:1;
	uint8_t		reverse:1;
	uint8_t		recursive:1;
	uint8_t		modtime:1;
	int			largest;
	char		*directory;
}				t_info;

struct			s_parse_options {
	char	flag;
	int		(*func)(t_info *);
}				t_parse_options;

typedef struct	s_filelist {
	char				*path;
	char				*name;
	float				*totalblocks;
	struct s_filelist	*directory;
	struct stat			*stbuf;
	struct s_info		*info;
	struct s_filelist	*next;
}				t_filelist;

/*
** options.c
*/

int				all(t_info *file_info);
int				modtime(t_info *file_info);
int				longlist(t_info *file_info);
int				recursive(t_info *file_info);
int				reverse(t_info *file_info);

/*
** list.c
*/
int				add_file(t_filelist **filelist, t_filelist *file_info,
					struct dirent *dir_info);
int				fixme_add_file(t_filelist *filelist, char *name,
							t_info *file_info, char *dirname);
int				add_stats(t_filelist *filelist, char *dirname);
void			free_link_data(t_filelist *filelist);
char			*build_path(char *base, char *addition);

/*
** ft_ls.c
*/
void			printdata(t_filelist *filelist);
int				ft_ls(t_info *file_info);
int				itterate_search(t_info *file_info, char *str);

/*
** sort.c
*/
void			sort_data(t_filelist **filelist);
t_filelist		*time_sort(t_filelist *filelist);
t_filelist		*alpha_sort(t_filelist *filelist);
t_filelist		*reverse_sort(t_filelist *filelist);

/*
** permissions.c
*/
char			*mode_parse(mode_t mode);

/*
** utils.c
*/
t_timespec		*parse_time(char *str);
int				hiddenfile(t_info *file_info, char *str);
int				init(t_filelist **filelist);
void			ls_parse_options(char *argv[], int argc, t_info *file_info);

/*
** directory_handle.c
*/
void			make_directory(t_filelist *filelist);
void			populate_directory(t_filelist *filelist);
void			fetch_directories(t_filelist *filelist);

#endif
