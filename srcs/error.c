/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:10:15 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:10:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Function which print the right error message
*/

void	dump_err(char errcode)
{
	t_keyval err[6];
	int 	i;

	err[0] = KEY_VAL(BADQUOTES, BADQUOTES_STR);
	err[1] = KEY_VAL(NOMEM, NOMEM_STR);
	err[2] = KEY_VAL(NODIR, NODIR_STR);
	err[3] = KEY_VAL(FAILSETSIGHDLR, FAILSETSIGHDLR_STR);
	err[4] = KEY_VAL(FAILREAD, FAILREAD_STR);
	err[5] = KEY_VAL(0, NULL);
	i = 0;
	while (errcode != err[i].key && err[i].key)
		i++;
	if (err[i].key)
		ft_putstr_fd(err[i].val, STDERR_FILENO);
}

/*
** Print the error message and exit
*/

void		fatal_err(char errcode, t_ctx *ctx)
{
	dump_err(errcode);
	wrap_exit(EXIT_FAILURE, ctx);
}

/*
** Free everything
*/

void	wrap_exit(int status, t_ctx *ctx)
{
	if (ctx->line.line)
	//ft_dlsthead(&ctx->line);//
		ft_dlstdel(&ctx->line.line, &ft_memdel);
	if (ctx->line.yank)
	//ft_dlsthead(&ctx->yank);//
		ft_dlstdel(&ctx->line.yank, &ft_memdel);

//	if (ctx->line.linestate)
//		stack_del(&ctx->line.linestate);

	if (ctx->hist.list)//faire une fonction dédiée
	{
	////ft_dlsthead(&ctx->histlist);//
		if (ctx->hist.list->next)
		{
			trim_history(&ctx->hist.list->next, ft_astr_getval(ctx->locals, "HISTFILESIZE"));
			save_history(ctx->locals, ctx->hist.list->next);
			ctx->hist.list = ctx->hist.list->next;
			ft_dlstdelone(&ctx->hist.list->prev, &ft_memdel);
			ft_dlstdel(&ctx->hist.list, &del_histentry);
		}
		else
			ft_dlstdelone(&ctx->hist.list, &ft_memdel);
	}
	if (ctx->environ)
		ft_astr_clear(&ctx->environ);
	if (ctx->locals)
		ft_astr_clear(&ctx->locals);
	write(STDOUT_FILENO, "exit\n", 6);
	if (ctx->line_edition == true)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->oldtios);	
	exit(status);
}
