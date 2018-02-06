/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:44:10 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 16:45:11 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

void		ft_putnbr(long n);

void		ft_putstr_fd(char const *s, int fd);

void		ft_putstr(char const *s);

void		ft_putendl(char const *s);

void		ft_putendl_fd(char const *s, int fd);

int			get_next_line(const int fd, char **line);

#endif