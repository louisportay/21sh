/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:21:49 by lportay           #+#    #+#             */
/*   Updated: 2017/10/13 17:04:30 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

# include "ft_printf.h"

int		get_next_line(const int fd, char **line);
int		ft_getchar(void);
int		ft_printf(const char *restrict format, ...);
void	ft_putendl(char const *s);
void	ft_putstr(char const *s);
void	ft_putstr_fd(int fd, char const *s);
void	ft_putnbr(long n);
int	ft_putchar(int c);
int	ft_putchar_fd(int fd, int c);
void	ft_putnchar(char c, size_t n);
void	ft_putnchar_fd(int fd, char c, size_t n);

#endif
