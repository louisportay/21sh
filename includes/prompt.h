/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:03:42 by lportay           #+#    #+#             */
/*   Updated: 2018/03/13 17:59:52 by lportay          ###   ########.fr       */
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

# define PROMPT_FLAG(FUNC, FLAG)	(t_prompt_flag){.func = FUNC, .flag = FLAG}

typedef struct s_ctx	t_ctx;

typedef struct			s_prompt_flag
{
	void				(*fun)(t_ctx *env);
	char				flag;
}						t_prompt_flag;

void					print_prompt(void);
void					print_flag(t_ctx *ctx, char *s);


void	d_flag(t_ctx *ctx);
void	cap_h_flag(t_ctx *ctx);
void	l_flag(t_ctx *ctx);
void	s_flag(t_ctx *ctx);
void	u_flag(t_ctx *ctx);
void	w_flag(t_ctx *ctx);
void	cap_w_flag(t_ctx *ctx);
void	bang_flag(t_ctx *ctx);

#endif
