/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:42:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/05 18:34:58 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "parser.h"

int						panic_exit(int code, char *msg)
{
	ft_putstr_fd(STDERR_FILENO, msg);
	exit(code);
	return (code);
}

/*
**	UNSAFE IMPLEMENTATION VALID IN CURRENT CONTEXT
**	DO NOT USE OTHERWISE OR PROTECT IT
*/

static int				l_hand_redirs(t_token **token, t_redir *redirs[2])
{
	if (redirs[0] == NULL)
		redirs[0] = (t_redir *)*token;
	else
		redirs[1]->next = *token;
	redirs[1] = (t_redir *)*token;
	*token = (*token)->next;
	return (1);
}

static int				l_hand_assign(t_token **token, t_token *assign[2])
{
	if (assign[0] == NULL)
		assign[0] = *token;
	else
		assign[1]->next = *token;
	assign[1] = *token;
	*token = (*token)->next;
	return (1);
}

static int				get_next(t_token **token,
									t_token *assign[2],
									t_redir *redirs[2])
{
	if (*token == NULL)
		return (0);
	else if ((*token)->type == ASSIGNMENT_WORD)
		return (l_hand_assign(token, assign));
	else if (((*token)->type & REDIRS) != 0)
		return (l_hand_redirs(token, redirs));
	else
		return (0);
}

static void				get_assigns(t_token **token,
									t_token *assign[2],
									t_redir *redirs[2])
{
	while (get_next(token, assign, redirs) != 0)
		;
}

#include <stdio.h>//
void ft_astr_print(char **env)
{
	int i = 0;
	while (env[i] != NULL)
		printf("env[%d]: '%s'\n", i, env[i]);
}

int						ft21_parse(t_token *token, char **env)
{
	t_proc				*proc;
	t_token				*assign[2];
	t_redir				*redirs[2];

	ft_astr_print(env);
	while (token != NULL)
	{
		if ((proc = (t_proc *)ft_memalloc(sizeof(t_proc))) != NULL)
			return (panic_exit(MALLOC_FAILURE, MALLOC_FAILMSG));
		proc->env = ft_astr_dup(env);
		redirs[0] = NULL;
		assign[0] = NULL;
		get_assigns(&token, assign, redirs);
		update_env(&proc->env, assign[0]);
		proc->redirs = redirs[0];
		ft_astr_print(proc->env);
		break ;
	}
	return (1);
}


