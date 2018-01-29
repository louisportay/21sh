/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:03:41 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 16:59:27 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KVP_H
# define KVP_H

# define KVP(KEY, VAL)				(t_kvp){.key = KEY, .val = VAL}

typedef struct	s_kvp
{
	char *key;
	char *val;
}				t_kvp;

char	*get_kvp(const char *name, t_kvp *kvp);
int		set_kvp(char *name, const char *value, t_kvp **addr_kvp);
void	delete_kvp(t_kvp **addr_kvp);
void	dump_kvp(t_kvp *environ);
t_kvp	*copy_kvp_env(char **env);
t_kvp	*copy_stack_kvp(t_kvp *stack_kvp, size_t len);

#endif
