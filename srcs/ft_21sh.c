/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:23:05 by lportay           #+#    #+#             */
/*   Updated: 2018/02/19 11:29:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ctx *get_ctxaddr(t_ctx *ctxaddr)
{
	static t_ctx *ctx = NULL;

	if (ctxaddr)
		ctx = ctxaddr;
	return (ctx);
}

void	vingtetunsh(char **av, char  **environ)
{
	t_ctx	ctx;
	char	ret;
	t_job *extree;

	if ((ret = init(&ctx, av, environ)) != SUCCESS)
		fatal_err(ret, &ctx);

	while (1)//
	{
		wrap_lineread(&ctx, &ctx.line, PS1);

		if (ctx.line.split_line)
			ctx.toklist = tokenizer(ctx.line.split_line);
		if (ctx.toklist != NULL)
			extree = parse(ctx.toklist);
		delete_toklist(&ctx.toklist);
		if (extree != NULL)
		{
			// HERE WILL THE EXPANSION GO IN NEAR FUTURE
			exec(extree);
		        job_clear(&extree);
		}
		if (ctx.line.line_saved == false)
			ft_dlstdel(&ctx.line.split_line, &delvoid);
		else//
			ft_dlstremove(&ctx.line.final_newline, &delvoid);
	}
	wrap_exit(EXIT_SUCCESS, &ctx);
}
