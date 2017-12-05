/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:13:02 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 01:37:18 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"
/*
** https://www.linuxquestions.org/questions/programming-9/ceiling-function-c-programming-637404/
*/ 
# define CEILING_POS(X) ((X-(int)(X)) > 0 ? (int)(X+1) : (int)(X))

typedef struct	s_info
{
	uint8_t			all:1,longlist:1,reverse:1,recursive:1,modtime:1;
	int				largest;
	char			*directory;
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
	struct stat 		*stbuf;
	struct s_info		*info;
	struct s_filelist	*next;
}				t_filelist;

/*
** options.c
*/

int			all(t_info *file_info);
int			modtime(t_info *file_info);
int			longlist(t_info *file_info);
int			recursive(t_info *file_info);
int			reverse(t_info *file_info);

/*
** list.c
*/
// int			add_file(t_filelist *, char	*, t_info *, char *);
int			add_file(t_filelist **filelist, t_filelist *file_info, struct dirent *dir_info);
int			fixme_add_file(t_filelist *filelist, char	*name, t_info *file_info, char *dirname);
int			add_stats(t_filelist *filelist, char *);
void		free_link_data(t_filelist *filelist);
char		*build_path(char *base, char *addition);

/*
** ft_ls.c
*/
char		*make_dir_format(char *str);
int			hiddenfile(t_info *filelist, char *str);
void		sort_data(t_filelist **filelist);
void		fetch_directories(t_filelist *filelist);

/*
** sort.c
*/
t_filelist	*time_sort(t_filelist *filelist);
t_filelist	*alpha_sort(t_filelist *filelist);
t_filelist	*reverse_sort(t_filelist *filelist);

/*
** permissions.c
*/
char		*mode_parse(mode_t mode);

#endif