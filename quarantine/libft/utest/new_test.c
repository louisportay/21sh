/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:46:37 by lportay           #+#    #+#             */
/*   Updated: 2017/11/28 11:08:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Cree un nouvel element de liste contenant le nom du test
** et un pointeur sur fonction du test a faire.
*/

t_utest	*new_utest(char *testname, int (*f)(void))
{
	t_utest	*elem;

	if (!testname || !f)
		return (NULL);
	elem = (t_utest *)malloc(sizeof(t_utest));
	elem->testname = ft_strdup(testname);
	elem->testfunc = f;
	return (elem);
}
