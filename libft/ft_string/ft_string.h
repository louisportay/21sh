/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:39:51 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/06 16:30:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <stdint.h>

void			ft_bzero(void *s, size_t n);

void			ft_ultobuf(unsigned long long l, size_t base, u_char upper,
							char *buf);
void			ft_ltobuf(long long l, size_t base, u_char upper, char *buf);

void			*ft_memalloc(size_t size);
void			*ft_pmemalloc(size_t size, void (*on_error)(int), int status);

void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_lwidth(long nb);

char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinc(char const *s1, char const *s2, char const c);
char			*ft_strnjoin(char const *s1, char const *s2, size_t n);

char			*ft_strnew(size_t size);
void			ft_strdel(char **str);
void			ft_memdel(void **ap);

char			*ft_strndup(const char *s1, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strpdup(const char *s1, const char *s2);
void			*ft_memdup(void *src, size_t n);

size_t			ft_strlen(const char *s);

int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);

char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);

char			*ft_basename(char *path);
char			*ft_dirname(char *path);
char			*fullpath(char *dirname, char *basename);

size_t			ft_stroccur(const char *s, char c);

char			*ft_itoa(long n);
int				ft_atoi(const char *str);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *big, const char *little);
char 			*randstring(int len);
int				ft_strindex(char *str, char c);

#endif
