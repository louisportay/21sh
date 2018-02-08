/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_darray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 19:34:10 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 19:35:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_darray(int **tab, int lin, int col, int val)
{
	int i;
	int j;

	i = 0;
	while (i < lin)
	{
		j = 0;
		while (j < col)
			tab[i][j++] = val;
		i++;
	}
}
