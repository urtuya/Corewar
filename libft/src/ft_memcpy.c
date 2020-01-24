/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <vellery-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 03:45:22 by vellery-          #+#    #+#             */
/*   Updated: 2020/01/24 12:49:02 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*from;
	unsigned char	*to;

	if (n == 0 || dst == src)
		return (dst);
	i = 0;
	from = (unsigned char*)src;
	to = (unsigned char*)dst;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	// while (*from < *to)
	// {
	// 	*from = *to;
	// 	from++;
	// 	to++;
	// }
	return (dst);
}
