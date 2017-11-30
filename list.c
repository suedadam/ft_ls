/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 21:21:05 by asyed             #+#    #+#             */
/*   Updated: 2017/11/29 22:38:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>

int	add_file(t_filelist *filelist, char	*name, t_info *file_info)
{
	t_filelist *current_list;

	if (filelist->name)
	{
		current_list = (t_filelist *)ft_memalloc(sizeof(t_filelist));
		if (!current_list)
		{
			printf("Failed to malloc(newlink) %s\n", strerror(errno));
			return (0);
		}
		filelist->next = current_list;
	}
	else
		current_list = filelist;
	current_list->info = file_info;
	current_list->name = ft_strdup(name);
	add_stats(current_list);
	return (1);
}