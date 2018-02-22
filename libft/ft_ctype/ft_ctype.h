/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:47:03 by lportay           #+#    #+#             */
/*   Updated: 2018/02/22 11:50:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CTYPE_H
# define FT_CTYPE_H

#include <wchar.h>

int		ft_isalnum(int c);
int		ft_isnumber(char *str);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isunicode(wchar_t a);
int		ft_isspace(int c);

#endif
