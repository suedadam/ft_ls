/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:13:02 by asyed             #+#    #+#             */
/*   Updated: 2017/11/28 03:00:19 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdint.h>

typedef struct	s_info
{
	struct stat		*stats;
	uint8_t			all:1,longlist:1,reverse:1,recursive:1,modtime:1;
}				t_info;

struct			s_parse_options {
	char	flag;
	int		(*func)(t_info *);
}				t_parse_options;

/*
** options.c
*/

int		all(t_info *file_info);
int		modtime(t_info *file_info);
int		longlist(t_info *file_info);
int		recursive(t_info *file_info);
int		reverse(t_info *file_info);

#endif