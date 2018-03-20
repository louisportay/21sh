/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:18:08 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 14:44:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KVP_H
# define KVP_H

typedef struct s_kvp	t_kvp;

enum	e_kvp_type
{
	INT_STR,
	STR_STR,
};

struct					s_kvp
{
	void				*key;
	void				*val;
	enum e_kvp_type		typ;
};

#endif
