/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:55:42 by lportay           #+#    #+#             */
/*   Updated: 2017/11/28 11:08:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_test(void *test, size_t test_size)
{
	(void)test_size;
	ft_strdel(&((t_utest *)test)->testname);
	free(test);
}
