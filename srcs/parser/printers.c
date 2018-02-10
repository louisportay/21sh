/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 20:10:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					ptok_print(struct s_ptok *tokens)
{
	(void)tokens;
	return ;
}

void					asmt_print(t_asmt *asmt)
{
	while (asmt != NULL)
	{
		printf("%s=%s\n", asmt->key, asmt->value);
		asmt = asmt->next;
	}
}

void					astr_print(char **astr)
{
	int					i;

	i = 0;
	while (astr[i] != NULL)
	{
		printf("argv[%d]: %s\n", i, astr[i]);
		i++;
	}
}
