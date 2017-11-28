/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 02:59:17 by asyed             #+#    #+#             */
/*   Updated: 2017/11/28 02:59:29 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		all(t_info *file_info)
{
	file_info->all = 1;
	return (1);
}

int		modtime(t_info *file_info)
{
	file_info->modtime = 1;
	return (1);
}

int		longlist(t_info *file_info)
{
	file_info->longlist = 1;
	return (1);
}

int		recursive(t_info *file_info)
{
	file_info->recursive = 1;
	return (1);
}

int		reverse(t_info *file_info)
{
	file_info->reverse = 1;
	return (1);
}
