/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:07:07 by lportay           #+#    #+#             */
/*   Updated: 2017/11/27 10:11:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <wchar.h>
# include <stdarg.h>
# include <stdbool.h>
# ifdef __linux__
#  include <stdint.h>
# endif

# define THREE_BITS 7
# define FOUR_BITS 15
# define FIVE_BITS 31
# define SIX_BITS 63
# define TWO_MASK 32960
# define THREE_MASK 8421600
# define FOUR_MASK 2155905264

/*
** fl -> flags + int en [10]
** lg -> long argument
** str -> chaine de char pour %s
** s -> chaine tampon
** ulg -> Ulong arg
** wstr -> string de wchar
** first -> boléenne
** j -> char imprimés ?
** ap -> arguments
*/

typedef struct	s_printf
{
	char		buf[BUFF_SIZE];
	int			**fl;
	long		*lg;
	char		**str;
	wchar_t		**wstr;
	char		*s;
	int			first;
	size_t		j;
	va_list		ap;
}				t_printf;

int				is_specifier(char c);
int				is_flag(char c);
int				is_arg(char *format);
int				is_oct_hex(int j);
void			print_hexa(t_printf *l, int *i, int j);
void			print_octal(t_printf *l, int *i, int j);
void			print_unsigned(t_printf *l, int *i, int j);
void			print_d(t_printf *l, int *i, int j);
void			print_wstr(t_printf *l, int *i, wchar_t *wstr);
void			print_str(t_printf *l, int *i, char *s);
void			print_wchar(t_printf *l, int *i, long lg);
void			print_char(t_printf *l, int *i, long lg);
void			print_pointer(t_printf *l, int *i, int j);
void			print_percent(t_printf *l, int *i);
void			print_argument(t_printf *l, int i);
void			print_input(t_printf *l, char *format, int *i);
int				count_percent(char *format);
wchar_t			*ft_strchr_greater(const wchar_t *s, int c);
size_t			bytewidth(wchar_t *wstr);
int				max_wchar(wchar_t *wstr, int i);
void			get_specifier(char f, t_printf *l, int i);
void			get_format(char f, int *l);
void			get_flags(char f, int *l);
void			get_width_prec(t_printf *i, char **f, int *l);
int				check_input(char *format, t_printf *l);
int				check_format(t_printf *t, int *l);
void			check_specifier(int *l);
void			cast_d(t_printf *l, int i, int j);
void			cast_s(t_printf *l, int i);

#endif
