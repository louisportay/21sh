/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:44:10 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/15 17:50:24 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

#define BUFF_SIZE 4096
# define RESET			"\e[0m"
# define BOLD			"\e[1m"
# define ITALIC			"\e[3m"
# define STRIKETHROUGH	"\e[9m"
# define BLACK			"\e[30m"
# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define YELLOW			"\e[33m"
# define BLUE			"\e[34m"
# define MAGENTA		"\e[35m"
# define CYAN			"\e[36m"
# define LIGHT_GRAY		"\e[37m"
# define DEFAULT		"\e[39m"
# define DARK_GRAY		"\e[90m"
# define LIGHT_RED		"\e[91m"
# define LIGHT_GREEN	"\e[92m"
# define LIGHT_YELLOW	"\e[93m"
# define LIGHT_BLUE		"\e[94m"
# define LIGHT_MAGENTA	"\e[95m"
# define LIGHT_CYAN		"\e[96m"
# define WHITE			"\e[97m"


#include <unistd.h>
#include "ft_string.h"

void		ft_putnbr(long n);

void		ft_putstr_fd(char const *s, int fd);

void		ft_putstr(char const *s);

void		ft_putendl(char const *s);

void		ft_putendl_fd(char const *s, int fd);

int			get_next_line(const int fd, char **line);

int			ft_tmpfile(void);

#endif
