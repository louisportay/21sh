/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:00:33 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/26 15:36:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ASTR_H
# define FT_ASTR_H

# include <stdlib.h>
# include "ft_string.h"

int			ft_astr_append(char ***astr, char *value);

int			ft_astr_beginswith(char **astr, char *value);
int			ft_astr_nbeginswith(char **astr, char *value, size_t pos);

int			ft_astr_copy(char **dst, char **src);
int			ft_astr_ncopy(char **dst, char **src, size_t n);
int			ft_astr_deepcopy(char **dst, char **src);
int			ft_astr_ndeepcopy(char **dst, char **src, size_t n);

char		**ft_astr_dup(char **astr);

void		ft_astr_foreach(char **astr, void (*act)());

void		ft_astr_free(char ***astr);
void		ft_astr_nfree(char **astr, size_t n);
int			ft_astr_clear(char ***astr);
int			astr_rmdup(char ***astr);
int			ft_astr_nclear(char **astr, size_t n, void **head);

size_t		ft_astr_len(char **arr);

char		*ft_astr_remove_at(char ***astr, size_t index);

char		*ft_astr_find(char **astr, char *str);
char		*ft_astr_findn(char **astr, char *str, size_t n);

char		*ft_astr_findpart(char **astr, char *str, char *(*mapper)(char *));

char		*ft_env_find(char **env, char *key);

int			ft_astr_getkey(char **env, char *key, int pos);
char		*ft_astr_getval(char **env, char *key);
int			ft_astr_getlowkey(char **arr, char *key);

void		ft_astr_replace(char **astr, int i, char *new_val);

#endif
