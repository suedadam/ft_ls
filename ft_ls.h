/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:13:02 by asyed             #+#    #+#             */
/*   Updated: 2017/11/29 23:22:07 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"

typedef struct	s_info
{
	uint8_t			all:1,longlist:1,reverse:1,recursive:1,modtime:1;
}				t_info;

struct			s_parse_options {
	char	flag;
	int		(*func)(t_info *);
}				t_parse_options;

typedef struct	s_filelist {
	char				*name;
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
int			add_file(t_filelist*, char*, t_info*);

/*
** ft_ls.c
*/
int			add_stats(t_filelist *filelist);

/*
** sort.c
*/
t_filelist	*time_sort(t_filelist *filelist);

#endif