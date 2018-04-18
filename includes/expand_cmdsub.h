/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdsub.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:13:43 by lportay           #+#    #+#             */
/*   Updated: 2018/04/18 17:18:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_CMDSUB_H
# define EXPAND_CMDSUB_H

#include "ft_42sh.h"

int		expand_cmdsub(char *s, char **new_s, t_ctx *ctx);

#endif
