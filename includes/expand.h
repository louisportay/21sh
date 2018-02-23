/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:48:30 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 21:37:34 by vbastion         ###   ########.fr       */
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

typedef struct s_job		t_job;
typedef struct s_proc		t_proc;
typedef struct s_ctx		t_ctx;

int							expand(char *str, t_ctx *ctx,
									void *(*converter)(t_list *lst),
									void **conv);

char						*ft_list_join(t_list *head, char *jstr, char *pre);
void						ft_list_insert_last(t_list **head, t_list **curr,
												t_list *tmp);

int							expand_job(t_job *j, t_ctx *ctx, int *exp_err);
int							expand_proc(t_proc *p, t_ctx *ctx);
int							expand_asmt(t_proc *p, t_ctx *ctx);

#endif
