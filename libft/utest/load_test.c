/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:48:51 by lportay           #+#    #+#             */
/*   Updated: 2017/11/28 11:11:29 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	load_test(t_list **alst, t_utest *test)
{
	t_list *testinlist;

	testinlist = ft_lstnewaddr(test, sizeof (t_utest *));
	if (!(*alst))
		*alst = testinlist;
	else
		ft_lstaddend(alst, testinlist);
}
