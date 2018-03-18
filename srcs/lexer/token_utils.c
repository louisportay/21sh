/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 19:08:40 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 15:13:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** add NAME
*/

void	init_token_table(t_kvp *tok)
{
	tok[0] = (t_kvp){.key=(void *)NEWLINE, .val=(char *)"NEWLINE", .typ=INT_STR};
	tok[1] = (t_kvp){.key=(void *)SEMICOL, .val=(char *)"SEMICOL", .typ=INT_STR};
	tok[2] = (t_kvp){.key=(void *)IO_NUMBER, .val=(char *)"IO_NUMBER", .typ=INT_STR};
	tok[3] = (t_kvp){.key=(void *)WORD, .val=(char *)"WORD", .typ=INT_STR};
	tok[4] = (t_kvp){.key=(void *)ASSIGNMENT_WORD,
		.val=(char *)"ASSIGNMENT_WORD", .typ=INT_STR};
	tok[5] = (t_kvp){.key=(void *)OR, .val=(char *)"OR", .typ=INT_STR};
	tok[6] = (t_kvp){.key=(void *)AND, .val=(char *)"AND", .typ=INT_STR};
	tok[7] = (t_kvp){.key=(void *)LESS, .val=(char *)"LESS", .typ=INT_STR};
	tok[8] = (t_kvp){.key=(void *)GREAT, .val=(char *)"GREAT", .typ=INT_STR};
	tok[9] = (t_kvp){.key=(void *)OR_IF, .val=(char *)"OR_IF", .typ=INT_STR};
	tok[10] =(t_kvp){.key=(void *)AND_IF, .val=(char *)"AND_IF", .typ=INT_STR};
	tok[11] =(t_kvp){.key=(void *)DLESS, .val=(char *)"DLESS", .typ=INT_STR};
	tok[12] =(t_kvp){.key=(void *)DGREAT, .val=(char *)"DGREAT", .typ=INT_STR};
	tok[13] =(t_kvp){.key=(void *)LESSAND, .val=(char *)"LESSAND", .typ=INT_STR};
	tok[14] =(t_kvp){.key=(void *)GREATAND, .val=(char *)"GREATAND", .typ=INT_STR};
	tok[15] =(t_kvp){.key=(void *)TLESS, .val=(char *)"TLESS", .typ=INT_STR};
	tok[16] =(t_kvp){.key=(void *)ANDGREAT, .val=(char *)"ANDGREAT", .typ=INT_STR};
	tok[17] =(t_kvp){.key=(void *)ANDDGREAT, .val=(char *)"ANDDGREAT", .typ=INT_STR};
	tok[18] =(t_kvp){.key=(void *)COMMENT, .val=(char *)"COMMENT", .typ=INT_STR};
	tok[19] =(t_kvp){.key=(void *)0, .val=NULL, .typ=INT_STR};
}

void	print_toklist(t_token *toklist)
{
	t_kvp	tok[20];
	int		i;

	init_token_table(tok);
	while (toklist)
	{
		dump_token(toklist);
		ft_putstr(" Type: ");
		i = 0;
		while ((unsigned long)tok[i].key != toklist->type && tok[i].key)
				i++;
		ft_putstr(tok[i].val);
		write(STDOUT_FILENO, "\n", 1);
		toklist = toklist->next;
	}
}

void	dump_token(t_token *tok)
{
	t_dlist *tmp;

	tmp = tok->first_letter;
	while (tmp != tok->last_letter)
	{
		write(STDOUT_FILENO, tmp->data, 1);
		tmp = tmp->next;
	}
	write(STDOUT_FILENO, tmp->data, 1);
}

t_token		*new_token(t_dlist *line)
{
	t_token *new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	new->first_letter = line;
	new->last_letter = NULL;
	new->next = NULL;
	return (new);
}
