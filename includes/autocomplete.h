/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 19:45:05 by lportay           #+#    #+#             */
/*   Updated: 2018/04/13 10:21:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

typedef struct	s_string
{
	char		*s;
	unsigned	len;
}				t_string;

void			print_results(t_dlist *matches, int maxlen, unsigned ws_col);
void			complete_line(t_line *l, char *fullpath, unsigned len);

void			complete_binary(t_ctx *ctx, t_line *l, char **p, t_string str);
void			complete_path(t_ctx *ctx, t_line *l, t_string str);

void			expand_tilde_autocomplete(char **s, char *home);
int				dlst_hasblank(t_dlist *dlst);
int				entry_already_in_list(char *name, t_dlist *matches);
void			restore_line(t_ctx *ctx, t_line *l);

#endif
