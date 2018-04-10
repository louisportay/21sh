/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:28:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 12:05:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <wchar.h>
# include <locale.h>

# include <sys/types.h>

# include "qbuf.h"

# define FT_PBSZ 2048
# define FT_TMPBSZ 100
# define FPF_CONV ("sSpdDioOuUxXcC%bBnfFeE")
# define FPF_FLAG ("#0- +")
# define FT_CONVCNT 22
# define FT_BASE_U ("0123456789ABCDEF")
# define FT_BASE_L ("0123456789abcdef")
# define BIG_WS ("                                ")
# define BIG_00 ("00000000000000000000000000000000")
# define BIG_WS_SZ 32

typedef int					(*t_handler)();

/*
**	FLAG:
**		1: hh,	2: h,	4: l,	8: ll,	16: j,	32: z
**	then shifted by 8
**		1: #,	2: 0,	4: -,	8: sp,	16: +
*/

typedef struct				s_flag
{
	int						id;
	char					c;
	size_t					min;
	size_t					pre;
	u_char					sz_flag;
	u_short					flag;
}							t_flag;

typedef enum				e_outtype
{
	FPF_FD = 0,
	FPF_S = 1,
	FPF_A = 2
}							t_outtype;

typedef union				u_output
{
	int						fd;
	char					*tar;
	char					**out;
}							t_output;

typedef struct				s_buf
{
	int						init;
	t_qbuf					*buf;
	char					tmp_buf[FT_TMPBSZ];
	enum e_outtype			type;
	union u_output			out;
	size_t					len;
}							t_buf;

typedef struct				s_exp
{
	char					*buf;
	size_t					len;
	double					d;
	size_t					sz;
	int						negpre;
	size_t					rem;
}							t_exp;

int							ft_printf(const char *format, ...);
int							ft_fprintf(FILE *stream, const char *format, ...);
int							ft_sprintf(char *str, const char *format, ...);
int							ft_snprintf(char *str, size_t size,
										const char *format, ...);
int							ft_dprintf(int fd, const char *format, ...);
int							ft_asprintf(char **str, const char *format, ...);
int							ft_asnprintf(char **str, size_t size,
											const char *format, ...);

int							ft_vprintf(const char *format, va_list ap);
int							ft_vfprintf(FILE *stream, const char *format,
										va_list ap);
int							ft_vsprintf(char *str, const char *format,
										va_list ap);
int							ft_vsnprintf(char *str, size_t size,
										const char *format, va_list ap);
int							ft_vdprintf(int fd, const char *format, va_list ap);
int							ft_vasprintf(char **str, const char *format,
											va_list ap);
int							ft_vasnprintf(char **str, size_t size,
											const char *format, va_list ap);

int							fpf_worker(const char *format, va_list ap);

/*
**	BUF
*/

t_buf						*fpf_buf_get(void);
void						fpf_buf_init(t_buf *buf);
int							fpf_buf_add(const char *str, size_t n);
int							fpf_buf_addc(const char c);
int							fpf_buf_addfillers(int ws, size_t n);
void						fpf_buf_flush(t_buf *buf);
int							fpf_buf_clear(t_buf *buf);
size_t						fpf_buf_gettotal(t_buf *buf);

/*
**	PRINTER
*/

int							fpf_print_dec(char **str, t_flag *flag,
											size_t *len);

/*
**	STRING OPS
*/

void						fpf_putstr_fd(const char *str, int fd);
void						fpf_putstr(const char *str);
size_t						fpf_strlen(const char *str);

char						*fpf_strcpy(char *dst, const char *src);
char						*fpf_strncpy(char *dst, const char *src,
											size_t len);
int							fpf_strcmp(const char *s1, const char *s2);
int							fpf_strncmp(const char *s1, const char *s2,
										size_t n);

int							fpf_handle_str(va_list *ap, t_flag *flag);
int							fpf_handle_lst(va_list *ap, t_flag *flag);
int							fpf_handle_ptr(va_list *ap, t_flag *flag);
int							fpf_handle_dec(va_list *ap, t_flag *flag);
int							fpf_handle_bde(va_list *ap, t_flag *flag);
int							fpf_handle_uns(va_list *ap, t_flag *flag);
int							fpf_handle_bun(va_list *ap, t_flag *flag);
int							fpf_handle_char(va_list *ap, t_flag *flag);
int							fpf_handle_bch(va_list *ap, t_flag *flag);
int							fpf_handle_pct(va_list *ap, t_flag *flag);
int							fpf_handle_bin(va_list *ap, t_flag *flag);
int							fpf_handle_n(va_list *ap, t_flag *flag);
int							fpf_handle_k(va_list *ap, t_flag *flag);
int							fpf_handle_flo(va_list *ap, t_flag *flag);
int							fpf_handle_exp(va_list *ap, t_flag *flag);

int							fpf_handle_color(const char *format, size_t *i);

void						fpf_strwithsize(char *str, t_flag *flag);
int							fpf_exchar_is_reserved(wint_t c);

/*
**	NUMBERS OP
*/

int							fpf_atoi(char const *str);
long						fpf_atol(char const *str);
int							fpf_get_base(t_flag *flag);
double						rounder(int p);

/*
**	FLAG
*/

int							fpf_handle_flag(const char *str, size_t *i,
											va_list ap);
int							fpf_flag_print(const char *str, size_t *i,
											t_flag *flag, va_list ap);
void						fpf_flag_clear(t_flag *flag);
void						fpf_correct_fmt(t_flag *flag);

/*
**	CHAR OP
*/

int							fpf_isspace(int c);
int							fpf_isnum(int c);
int							fpf_isalpha(int c);
char						*fpf_strchr(const char *str, int c);

/*
**	PADDING
*/

int							pad_before(t_flag *flag, size_t str_len);
int							pad_after(t_flag *flag, size_t str_len);

/*
**	CONVERSIONS
*/

void						fpf_ltobuf(long long l, size_t base, u_char upper,
										char *buf);
void						fpf_ultobuf(unsigned long long l, size_t base,
										u_char upper, char *buf);

int							fpf_putcharbuf(wint_t wi, char buf[4], size_t *sz);
int							fpf_bigcharsize(wint_t wi);
t_handler					fpf_ptrget(int id);

#endif
