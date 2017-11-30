/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:32:38 by asyed             #+#    #+#             */
/*   Updated: 2017/11/30 14:35:55 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(intmax_t n)
{
	size_t i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n /= 10)
		i++;
	return (i);
}