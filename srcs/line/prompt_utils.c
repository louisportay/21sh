/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 17:57:07 by lportay           #+#    #+#             */
/*   Updated: 2018/03/13 17:59:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_flag(t_ctx *ctx, char *s)
{
	ctx->cur_line->prompt_len +=
		write(STDOUT_FILENO, s, ft_strlen(s));
}
