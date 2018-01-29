/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:03:42 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 17:02:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define PS1 "PS1"
# define PS2 "PS2"
# define PS3 "PS3"
# define PS4 "PS4"

# define PS1_VAL  "=\\s=$ "
# define PS2_VAL "> "
# define PS3_VAL ""
# define PS4_VAL "+ "

#ifdef __linux__
# define CUSTOM_HOST_NAME_MAX HOST_NAME_MAX
#elif __APPLE__
# define CUSTOM_HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#endif

/*
** This must be $(NAME) in the makefile
*/

# define SHELLNAME "21sh"

# define PROMPT_FLAG(FUNC, FLAG)	(t_prompt_flag){.func = FUNC, .flag = FLAG}
typedef struct	s_prompt_flag
{
	void		(*func)(t_21sh *env);
	char		flag;
}				t_prompt_flag;

void	print_prompt(t_21sh *env);

#endif
