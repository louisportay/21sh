/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:23:20 by lportay           #+#    #+#             */
/*   Updated: 2018/04/13 14:13:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*get_string_to_complete(char **environ, t_dlist *line)
{
	t_dlist *tmp;
	t_dlist	*next;
	char	*s;
	char	*home;

	next = line->next;
	line->next = NULL;
	tmp = line;
	while (line->prev && ft_isblank(*(char *)line->data) == 0)
		line = line->prev;
	if (line->next == NULL && ft_isblank(*(char *)line->data) == 1)
	{
		if ((s = ft_strdup("./")) == NULL)
			fatal_err(NOMEM, get_ctxaddr());
	}
	else if ((s = str_from_dlst(line)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	if (!ft_strncmp(s, "~", 1) && (home = ft_astr_getval(environ, "HOME")))
		expand_tilde_autocomplete(&s, home);
	line = tmp;
	line->next = next;
	return (s);
}

void	print_results(t_ctx *ctx, t_line *l, t_dlist *matches,
							unsigned maxlen)
{
	t_dlist *tmp;
	int		entry_num;
	int		i;

	i = 0;
	tmp = l->line;
	entry_num = ctx->ws.ws_col / maxlen;
	go_end(ctx, l);
	write(STDOUT_FILENO, "\n", 1);
	while (matches)
	{
		ft_printf("%-*s", maxlen, (char *)matches->data);
		if (++i == entry_num)
		{
			write(STDOUT_FILENO, "\n", 1);
			i = 0;
		}
		matches = matches->next;
	}
	if (i != 0)
		write(STDOUT_FILENO, "\n", 1);
	reset_attributes(l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(ctx, l);
}

void	complete_line(t_ctx *ctx, t_line *l, char *fullpath, unsigned len)
{
	t_dlist *dlst;
	t_dlist *tmp;

	if ((dlst = dlst_from_str(fullpath + len)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	tmp = l->line->next;
	l->line->next = dlst->next;
	l->line->next->prev = l->line;
	ft_dlstend(&l->line);
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;
	ft_dlstdelone(&dlst, &delvoid);
	tmp = l->line;
	clear_line(ctx, l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(ctx, l);
}

void	autocomplete(t_ctx *ctx, t_line *l)
{
	t_string str;

	str.s = get_string_to_complete(ctx->environ, l->line);
	str.len = ft_strlen(str.s);
	if (str.len == 0 || str.len >= PATH_MAX)
		return (free(str.s));
	if (dlst_hasblank(l->line) == 1)
		complete_path(ctx, l, str);
	else
		complete_binary(ctx, l, ctx->path, str);
	free(str.s);
}
