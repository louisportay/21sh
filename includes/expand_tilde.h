/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:18:03 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 11:53:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_TILDE_H
# define EXPAND_TILDE_H

# include "ft_42sh.h"

# define USR_PATH ("/Users/")

typedef struct s_job		t_job;
typedef struct s_proc		t_proc;
typedef struct s_ctx		t_ctx;

int							expand_tilde(char *str, char **ret, t_ctx *ctx);

#endif
