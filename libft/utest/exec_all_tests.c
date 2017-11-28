/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:23:35 by lportay           #+#    #+#             */
/*   Updated: 2017/11/28 12:59:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		exec_all_tests(t_list *lst)
{
	int	ret;

	ret = 0;
	while (lst)
	{
		if (exec_test((t_utest *)lst->content) == -1)
			ret = -1;
		lst = lst->next;
	}
	return (ret);
}
