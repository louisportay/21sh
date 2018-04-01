/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:13:17 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 13:14:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRIDGE_H
# define BRIDGE_H

typedef struct s_list	t_list;

char					*list_flatten(t_list *list);

void					astr_to_buf(char **argv, t_qbuf *buf, int last);
void					astr_env_replace(char ***env, char *key, char *new_v);

#endif
