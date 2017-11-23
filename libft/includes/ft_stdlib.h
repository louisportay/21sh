/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:49:08 by lportay           #+#    #+#             */
/*   Updated: 2017/11/17 16:35:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H

int		abs(int x);
int		ft_atoi(const char *str);
int		ft_atoi_base(char *str, int base);
char	*ft_itoa(long n);
char	*ft_itoa_base(long value, int base);
char	*ft_itoa_base_u(unsigned long value, unsigned int base);
void	ft_swap(int *n, int *m);
void	ft_cswap(char *n, char *m);
void	ft_fswap(float *n, float *m);
int		ft_lwidth(long nb);
size_t	ft_bwidth(unsigned long value, int base);
int		**ft_darray(int lin, int col);
char	*ft_getenv(const char *name, char **env);
int		ft_setenv(const char *name, const char *value,
int		overwrite, char ***env);
int		ft_unsetenv(const char *name, char ***env);
char	**ft_copyenv(char **env);

#endif
