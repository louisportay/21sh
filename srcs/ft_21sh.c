/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:23:05 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 19:32:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ctx 				*get_ctxaddr(void)
{
	static t_ctx 	ctx;
	return (&ctx);
}

void	exec_pipe(t_dlist *input)
{
	//t_token *toklist;
	t_toklist	tklst;
	t_job		*extree;

	extree = NULL;
	tklst = tokenizer(input);
	//ajouter dans l'historique si on se retrouve avec une chaine valide
	if (toklist != NULL)
		extree = parse(toklist);
	delete_toklist(&toklist);
	if (extree != NULL)
	{
		exec(&extree);
		job_clear(&extree);
	}
}

void	vingtetunsh(char **av, char  **environ)
{
	t_ctx	*ctx;
	char	ret;

	ctx = get_ctxaddr();

	if ((ret = init(ctx, av, environ)) != SUCCESS)
		fatal_err(ret, ctx);

	while (1)
	{
		ft_readline(ctx, &ctx->line, PS1);
		exec_pipe(ctx->line.line);
//		ft_dlstdel(&ctx->line.split_line, &delvoid);
	}
}
