/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 22:58:00 by asyed             #+#    #+#             */
/*   Updated: 2017/11/30 02:09:24 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>


t_filelist	*time_sort(t_filelist *filelist)
{
	t_filelist **begin;
	t_filelist *placement;
	t_filelist *tmp;

	*begin = filelist;
	// tmp = filelist->next->next;
	// *begin = filelist->next;
	// (*begin)->next = filelist;
	// filelist->next = tmp;
	while (filelist && filelist->next)
	{
		if (filelist->stbuf->st_mtimespec.tv_nsec >
			filelist->next->stbuf->st_mtimespec.tv_nsec)
		{
			tmp = filelist->next->next;
			placement = filelist->next;
			placement->next = filelist;
			filelist->next = tmp;
		}
		else
		{
			filelist = filelist->next;
		}
	}
	return (*begin);
}