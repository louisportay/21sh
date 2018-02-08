/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utest.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:36:24 by lportay           #+#    #+#             */
/*   Updated: 2017/12/07 13:43:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTEST_H
# define UTEST_H

#include <sys/wait.h>

typedef struct	s_utest
{
	char		*testname;
	int			(*testfunc)(void);
}				t_utest;

t_utest			*new_utest(char *testname, int (*f)(void));
void			load_test(t_list **alst, t_utest *test);
void			del_test(void *test, size_t test_size);
int				exec_test(t_utest *test);
int				exec_all_tests(t_list *lst);

#endif
