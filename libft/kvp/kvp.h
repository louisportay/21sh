/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:18:08 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 19:32:22 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KVP_H
# define KVP_H

typedef struct	s_kvp t_kvp;

enum	kvp_type
{
	INT_STR,
	STR_STR,
};

struct s_kvp
{
	void			*key;
	void			*val;
	enum kvp_type 	typ;
};

#endif
