/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:27:54 by lportay           #+#    #+#             */
/*   Updated: 2018/01/29 18:00:24 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Replace ASSIGNMENT_WORD by WORD when character in the part before the '='
** character does not respect the NAME Posix rule
*/

static void	filter_assignment_word(t_token *toklist)
{
	t_dlist *tmp;

	tmp = toklist->first_letter;
	if (ft_isdigit(*(char *)tmp->content) == true || *(char *)tmp->content == '=')
			toklist->type = WORD;
	while (*(char *)tmp->content != '=' && toklist->type == ASSIGNMENT_WORD)
	{
		if (ft_isalnum(*(char *)tmp->content) == false && *(char *)tmp->content != '_')
			toklist->type = WORD;
		tmp = tmp->next;
	}
}

static void	get_right_op(t_redir *newtok, t_token *right_op)
{
	newtok->s_right_op = token_str(right_op);
	newtok->fd_right_op = 0;
	newtok->dash = false;

	if (is_number(newtok->s_right_op) == true)
		newtok->fd_right_op = ft_atoi(newtok->s_right_op);
	else if (is_number_w_dash(newtok->s_right_op) == true)
	{
		newtok->fd_right_op = ft_atoi(newtok->s_right_op);
		newtok->dash = true;
	}
	else if (*(char *)newtok->last_letter->content == '-')
		newtok->dash = true;
}

static int	filter_redir(t_token *toklist, t_token *prev)
{
	t_redir *tmp;

	if (!(toklist->next->type & (WORD | ASSIGNMENT_WORD)) || !(tmp = (t_redir *)malloc(sizeof(t_redir))))
		return (-1);
	prev->next = (t_token *)tmp;
	tmp->first_letter = toklist->first_letter;

	tmp->last_letter = toklist->next->last_letter;
	tmp->next = toklist->next->next;
	tmp->type = toklist->type;
	if (tmp->type & (LESS | DLESS | LESSAND | TLESS))
		tmp->left_op = STDIN_FILENO;
	else if (tmp->type & (GREAT | DGREAT | GREATAND | ANDGREAT))
		tmp->left_op = STDOUT_FILENO;
	get_right_op(tmp, toklist->next);
//	printf("left:%d|fd:%d|s:%s|dash:%d\n", tmp->left_op, tmp->fd_right_op, tmp->s_right_op, tmp->dash);
	free(toklist->next);
	free(toklist);
	return (SUCCESS);
}

/*
** IO_NUMBER filter
*/

static int	filter_io_number(t_token *toklist, t_token *prev)
{
	t_redir *tmp;
	char	*s;

	if (!(toklist->next->next->type & (WORD | ASSIGNMENT_WORD)) || !(tmp = (t_redir *)malloc(sizeof(t_redir))))
		return (-1);
	prev->next = (t_token *)tmp;
	tmp->first_letter = toklist->first_letter;
	tmp->last_letter = toklist->next->next->last_letter;
	tmp->next = toklist->next->next->next;
	tmp->type = toklist->next->type;
	s = token_str(toklist);
	tmp->left_op = ft_atoi(s);
	free(s);

	get_right_op(tmp, toklist->next->next);
//	printf("left:%d|fd:%d|s:%s|dash:%d\n", tmp->left_op, tmp->fd_right_op, tmp->s_right_op, tmp->dash);
	free(toklist->next->next);
	free(toklist->next);
	free(toklist);
	return (SUCCESS);
}

static void filter_bang(t_token *toklist)
{
	t_token *tmp;

	if (toklist->last_letter->next != toklist->next->first_letter)
			toklist->type = WORD;
	else if (toklist->next->type == WORD || toklist->next->type == ASSIGNMENT_WORD || toklist->next->type == BANG)
	{
		tmp = toklist->next;
		toklist->last_letter = tmp->last_letter;
		toklist->next = tmp->next;
		free(tmp);
	}
}

static int get_exp_token_type(t_token *tok)
{
	if (*(char *)tok->first_letter->content == '{')
		return (PARAM_EXP);
	else if (*(char *)tok->first_letter->content == '[')
		return (ARI_EXP);
	else if (*(char *)tok->first_letter->content == '(' && *(char *)tok->first_letter->next->content == '(')
		return (ARI_EXP);
	else if (*(char *)tok->first_letter->content == '(')
		return (CMD_SUB);
	else
		return (PARAM_EXP);
		
}

static void	filter_dollar(t_token *toklist)
{
	t_token *tmp;

	tmp = toklist->next;
	if (toklist->last_letter->next != tmp->first_letter || !(tmp->type & (WORD | ASSIGNMENT_WORD)))
	{
		toklist->type = WORD;
		return ;
	}

	toklist->type = get_exp_token_type(toklist->next);
	toklist->last_letter = tmp->last_letter;
	toklist->next = tmp->next;
	free(tmp);
}

/*
** Change the following tokens:

** ASSIGNMENT_WORD

** IO_NUMBER

** LESS		
** GREAT	
** DLESS	
** DGREAT	
** LESSAND	
** GREATAND	
** TLESS	
** ANDGREAT	

** DOLLAR	

** BANG		
** 
** Into:
**
** Complete redirections operations with both operands and the operator in a single token |OK|
** PARAM_EXP
** CMD_SUB  
** ARI_EXP  
**
** Return the first faulty redirection if any.
*/

t_token	*filter_tokens(t_token *toklist)
{
	t_token *prev;

	prev = toklist;
	toklist = toklist->next;
	while (toklist->type != NEWLINE)
	{
		if (toklist->type & ASSIGNMENT_WORD)
			filter_assignment_word(toklist);
		else if (toklist->type & IO_NUMBER)
		{
			if (filter_io_number(toklist, prev) == -1)
				return (toklist);
		}
		else if (toklist->type & (LESS | GREAT | DLESS | DGREAT | LESSAND | GREATAND | TLESS | ANDGREAT))
		{
			if (filter_redir(toklist, prev) == -1)
				return (toklist);
		}
		else if (toklist->type & BANG)
			filter_bang(toklist);
		else if (toklist->type & DOLLAR)
			filter_dollar(toklist);

		prev = prev->next;
		toklist = prev->next;
	}
	return (NULL);
}
