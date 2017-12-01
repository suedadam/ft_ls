/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:11:21 by asyed             #+#    #+#             */
/*   Updated: 2017/11/30 16:11:46 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>

char	*mode_parse(mode_t mode)
{
	char 		*perm;
	const char	perm_list[10] =  "rwxrwxrwx";
	int 		i;

	// perm_list = "rwxrwxrwx";
	perm = (char *)ft_memalloc(10 * sizeof(char));
	if (!perm)
	{
		printf("Failed to malloc(perm) %s \n", strerror(errno));
		return (NULL);
	}
	i = 0;
	while (i < 9)
	{
		perm[i] = (mode & (1 << (8 - i))) ? perm_list[i] : '-';
		i++;
	}
	return (perm);
}