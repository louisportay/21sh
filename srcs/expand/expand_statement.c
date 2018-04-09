/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_statement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:43:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 22:36:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

/*
** TO BE REDONE  (expand_braces)
** OK (tilde)
**
** INTERFACE WILL CHANGE (word_splitting)
** INTERFACE WILL CHANGE (filename)
** INTERFACE WILL CHANGE (pattern_matching)
** INTERFACE WILL CHANGE (remove_quote)
*/

int				expand_word(char **str, t_environ *env)
{
	char 		*tstr;
	t_membuf	mb;

	ft_mb_init(&mb);
	expand_braces(str);
	expand_tilde(str, &mb, env);
	expand_param(str, &mb, env);
	word_splitting(str, &mb, env);
	expand_filename(str, &mb, env);
	pattern_matching(str, &mb, env);
	remove_quote(str, &mb, env);
	return (EXP_OK);
}
