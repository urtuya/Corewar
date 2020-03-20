/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 23:57:59 by vellery-          #+#    #+#             */
/*   Updated: 2020/03/03 19:07:19 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	**ft_matrix(int stb, int str)
{
	int **mat;
	int i;
	int j;



	i = 0;
	if (!(mat = (int**)malloc(sizeof(int*) * str)))
		return (0);
	while (i < str)
	{
		if (!(mat[i] = (int*)malloc(sizeof(int) * stb)))
			return (ft_ex_matdel(mat, i));
		i++;
	}
	i = 0;
	while (i < str)
	{
		j = 0;
		while (j < stb)
		{
			mat[i][j] = 0;
			j++;
		}
		i++;
	}
	return (mat);
}
