/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:18:03 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 17:18:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_TILDE_H
# define EXPAND_TILDE_H

# include "ft_env.h"
# include "kvp.h"

# define USR_PATH ("/Users/")

int				expand_tilde(char **str, t_environ *env);

#endif
