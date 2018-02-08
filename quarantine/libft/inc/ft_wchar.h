/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:54:39 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 15:28:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WCHAR_H
# define FT_WCHAR_H

wchar_t		*ft_wcsdup(const wchar_t *s);
size_t		ft_wcslen(const wchar_t *s);
void		ft_wcstrdel(wchar_t **as);

#endif
