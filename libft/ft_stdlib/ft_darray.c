/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 19:31:32 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 19:39:28 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		**ft_darray(int lin, int col)
{
	int i;
	int **double_array;

	i = 0;
	if (!(double_array = (int **)malloc(sizeof(int *) * lin)))
		return (NULL);
	while (i < lin)
		if (!(double_array[i++] = (int *)malloc(sizeof(int) * col)))
			return (NULL);
	return (double_array);
}
