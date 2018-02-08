/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:22:24 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 16:45:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHER_H
# define OTHER_H

void	fill_array(int *array, int width, int i);
void	fill_darray(int **tab, int lin, int col, int val);
int		free_array(void ***a, void (*del)(void **));

#endif
