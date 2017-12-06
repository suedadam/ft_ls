/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:11:21 by asyed             #+#    #+#             */
/*   Updated: 2017/12/05 14:26:37 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

const char	g_perm_list[10] = "rwxrwxrwx";

char	*mode_parse(mode_t mode)
{
	char		*perm;
	int			i;

	perm = (char *)ft_memalloc(10 * sizeof(char));
	if (!perm)
	{
		ft_printf("Failed to malloc(perm) %s \n", strerror(errno));
		return (NULL);
	}
	i = 0;
	while (i < 9)
	{
		perm[i] = (mode & (1 << (8 - i))) ? g_perm_list[i] : '-';
		i++;
	}
	return (perm);
}
