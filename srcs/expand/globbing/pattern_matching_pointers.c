/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_pointers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:48:28 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 18:32:17 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int			f_star(char **matcher, t_mtok **tmp)
{
	if (*(*matcher + 1) != '*')
		*tmp = mtok_create(FILEN);
	else if (*(*matcher + 2) != '/')
		*tmp = mtok_create(FILEN);
	else
		*tmp = mtok_create(DIREC);
	*matcher += (*tmp)->type;
	return (*tmp == NULL ? -1 : 1);
}

static int			f_mark(char **matcher, t_mtok **tmp)
{
	*tmp = mtok_create(ANYSI);
	*matcher += 1;
	return (*tmp == NULL ? -1 : 1);
}

static int			f_brac(char **matcher, t_mtok **tmp)
{
	char		*beg;
	char		*end;
	char		*str;

	beg = *matcher + 1;
	end = (*beg == ']') ? beg + 1 : beg;
	while (*end != '\0' && *end != ']')
		end++;
	if (*end == '\0')
		return (0);
	if ((str = create_range(beg, end)) == NULL)
		return (-1);
	if ((ft_strrmdup(&str)) == NULL)
		return (-1);
	if ((*tmp = mtok_create_str(RANGE, str)) == NULL)
	{
		ft_strdel(&str);
		return (-1);
	}
	*matcher = end + 1;
	return (1);
}

static int			f_dflt(char **matcher, t_mtok **tmp)
{
	(void)tmp;
	ft_dprintf(STDERR_FILENO, "Error, you should not be here.\n%s\n", *matcher);
	return (-1);
}

t_mptr				get_matcher(int id)
{
	static const t_mptr	ptrs[3] = (const t_mptr[3]) { &f_star, &f_mark, &f_brac };

	return ((id < 0 || id >= SPEC_CHR_CNT) ? &f_dflt : ptrs[id]);
}
