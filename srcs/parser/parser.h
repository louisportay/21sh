/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:20:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/05 18:20:09 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_21sh.h"
# include "kvp.h"
# include "libft.h"
# include "exec.h"
# include "token.h"
# include "ft_string.h"
# include "qbuf.h"
# include "ft_dlst.h"
# include "ft_astr.h"

# ifndef REDIRS
#  define UNREDIRS LESS | GREAT | DLESS | DGREAT | LESSAND | GREATAND
#  define REDIRS UNREDIRS | TLESS | ANDGREAT
# endif

# define MALLOC_FAILURE 101
# define MALLOC_FAILMSG ("Could not allocate memory\n")


typedef struct s_node	t_node;

struct					s_node
{
	t_job				*on_ok;
	t_job				*on_err;
	t_job				*next;
};

int						ft21_parse(t_token *token, char **env);

void					update_env(char ***env, t_token *token);

#endif
