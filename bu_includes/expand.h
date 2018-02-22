/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:48:30 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/21 14:31:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "expand_braces.h"
# include "expand_tilde.h"
# include "expand_param.h"
# include "expand_quotes.h"

/*
**	HAS TO BE RENAMED "expand_path"
*/

# include "dir_explorer.h"

//	# include "expand_split.h"
//	# include "expand_quotes.h"

int							expand(char **str, t_ctx *ctx,
									void *(*converter)(t_list *lst),
									void **conv);

char						*ft_list_join(t_list *head, char *jstr, char *pre);
void						ft_list_insert_last(t_list **head, t_list **curr,
												t_list *tmp);

#endif
