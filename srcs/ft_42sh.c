/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:43:56 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/16 11:44:24 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_ctx	*get_ctxaddr(void)
{
	static t_ctx ctx;

	return (&ctx);
}

void	exec_loop(t_dlist *input)
{
	t_token *toklist;
	t_job	*extree;

	extree = NULL;
	toklist = NULL;
	if (input != NULL)
		toklist = tokenizer(input);
	if (toklist != NULL)
		extree = parse(toklist);
	delete_toklist(&toklist);
	if (extree != NULL)
		exec(extree);
}

void	vingtetunsh(char **av, char **environ)
{
	t_ctx	*ctx;
	char	ret;

	ctx = get_ctxaddr();
	if ((ret = init(ctx, av, environ)) != SUCCESS)
		fatal_err(ret, ctx);
	while (1)
	{
		ft_readline(ctx, &ctx->line, PS1);
		exec_loop(ctx->line.split_line);
		ft_dlstdel(&ctx->line.split_line, &delvoid);
	}
}
