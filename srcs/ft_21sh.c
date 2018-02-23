/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:23:05 by lportay           #+#    #+#             */
/*   Updated: 2018/02/23 19:08:19 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ctx 				*get_ctxaddr(t_ctx *ctxaddr)
{
	static t_ctx 	*ctx = NULL;

	if (ctxaddr)
		ctx = ctxaddr;
	return (ctx);
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
	{
		exec(extree);
		job_clear(&extree);
	}
}

void	vingtetunsh(char **av, char  **environ)
{
	t_ctx	ctx;
	char	ret;

	if ((ret = init(&ctx, av, environ)) != SUCCESS)
		fatal_err(ret, &ctx);

	while (1)//
	{
		wrap_lineread(&ctx, &ctx.line, PS1);

		exec_loop(ctx.line.split_line);

		if (ctx.line.line_saved == false)
			ft_dlstdel(&ctx.line.split_line, &delvoid);
		else//
			ft_dlstremove(&ctx.line.final_newline, &delvoid);
	}
	wrap_exit(EXIT_SUCCESS, &ctx);
}
