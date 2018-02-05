/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_statement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:43:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 16:51:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int				expand_word(char **str, t_environ *env)
{
	char 		*tstr;
	t_membuf	mb;

	ft_mb_init(&mb);
	expand_braces(str);					//	TO BE REDONE
	expand_tilde(str, &mb, env);		//	OK
	expand_param(str, &mb, env);
	word_splitting(str, &mb, env);		// INTERFACE WILL CHANGE
	expand_filename(str, &mb, env);		// INTERFACE WILL CHANGE
	pattern_matching(str, &mb, env);	// INTERFACE WILL CHANGE
	remove_quote(str, &mb, env);		// INTERFACE WILL CHANGE
	return (EXP_OK);
}
