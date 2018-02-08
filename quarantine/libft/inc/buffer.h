/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:38:19 by lportay           #+#    #+#             */
/*   Updated: 2017/10/13 16:52:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

void	putc_in_buf(char a, char *buf, size_t *i);
void	putc_in_buf_fd(int fd, char a, char *buf, size_t *i);
void	puts_in_buf(char *s, char *buf, size_t *i);
void	putns_in_buf(int j, char *s, char *buf, size_t *i);
void	putnc_in_buf(int j, char a, char *buf, size_t *i);
void	putnbr_in_buf(int n, char *buf, size_t *i);
void	putwc_in_buf(wchar_t a, char *buf, size_t *i);
void	putws_in_buf(wchar_t *ws, char *buf, size_t *i);
void	putnws_in_buf(wchar_t *ws, int *n, char *buf, size_t *i);

#endif
