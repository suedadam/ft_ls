/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 22:58:00 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 14:43:57 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Shitty swap, I should swap the links themselves.
*/

void		swap_links(t_filelist *head, t_filelist *first, t_filelist *second)
{
	t_filelist *tmp;

	while (head && head->next && head->next != first)
		head = head->next;
	if (head->next == first)
	{
		tmp = second->next;
		head->next = second;
		second->next = first;
		first->next = tmp;
	}
}

void		sort_data(t_filelist **filelist)
{
	if ((*filelist)->info->modtime)
		*filelist = time_sort(*filelist);
	else if ((*filelist)->info->reverse)
		*filelist = reverse_sort(*filelist);
	else
		*filelist = alpha_sort(*filelist);
}

t_filelist	*time_sort(t_filelist *filelist)
{
	t_filelist *head;

	head = (t_filelist *)ft_memalloc(sizeof(t_filelist));
	head->next = filelist;
	while (filelist && filelist->next)
	{
		if (filelist->stbuf->st_mtimespec.tv_nsec >
			filelist->next->stbuf->st_mtimespec.tv_nsec)
		{
			swap_links(head, filelist, filelist->next);
			filelist = head->next;
		}
		else
			filelist = filelist->next;
	}
	return (head->next);
}

t_filelist	*alpha_sort(t_filelist *filelist)
{
	t_filelist *head;

	head = (t_filelist *)ft_memalloc(sizeof(t_filelist));
	head->next = filelist;
	while (filelist && filelist->next)
	{
		if (ft_strcmp(filelist->name, filelist->next->name) > 0)
		{
			swap_links(head, filelist, filelist->next);
			filelist = head->next;
		}
		else
			filelist = filelist->next;
	}
	return (head->next);
}

t_filelist	*reverse_sort(t_filelist *filelist)
{
	t_filelist *head;

	head = (t_filelist *)ft_memalloc(sizeof(t_filelist));
	head->next = filelist;
	while (filelist && filelist->next)
	{
		if (ft_strcmp(filelist->name, filelist->next->name) < 0)
		{
			swap_links(head, filelist, filelist->next);
			filelist = head->next;
		}
		else
			filelist = filelist->next;
	}
	return (head->next);
}
