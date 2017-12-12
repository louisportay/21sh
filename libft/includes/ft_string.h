/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:39:37 by lportay           #+#    #+#             */
/*   Updated: 2017/12/09 12:57:01 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_stroccur(const char *s, char c);
char	**ft_strsplit(char const *s, char c);
void	ft_strdel(char **as);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_dup(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strnew(size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_memdel(void **ap);
void	ft_bzero(void *s, size_t n);
void	ft_strlower(char *str);
void	ft_strupper(char *str);
void	ft_strrev(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strmatch(const char *s1, const char *s2);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strstri(const char *big, const char *little, size_t i);
void	ft_strrep(char **str, char *new_str);
char	**ft_strsplitquote(char const *s, char c);
char	*ft_strexpand(char *str, char c, char *expr);
char	*ft_basename(char *path);
char	*ft_dirname(char *path);
char 	*fullpath(char *dirname, char *basename);
char	*getpath(char *pathlist, char *exec);

#endif
