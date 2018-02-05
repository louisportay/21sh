/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 17:06:44 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/14 18:07:27 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "kvp.h"

void			*fk_conv(t_list *lst)
{
	return ((void *)lst);
}

static void		l_print(t_list *lst)
{
	while (lst != NULL)
	{
		ft_putstr("e: ");
		ft_putendl((char *)lst->content);
		lst = lst->next;
	}
}

int				main(int ac, char **av, char **env)
{
	char		*str;
	t_environ	envi;
	t_list		*lst;

	if (ac == 1)
	{
		ft_putstr_fd("Missing my arg.\n", STDERR_FILENO);
		return (1);
	}
	str = ft_strdup(av[1]);
	envi = (t_environ){.init = 1, .env = ft_env_copy(env), .locals = NULL};
	expand(&str, &envi, &fk_conv, (void **)&lst);
	l_print(lst);
	return (0);
}
