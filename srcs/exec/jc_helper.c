/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:07:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 16:07:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				get_ok_status(t_job *j)
{
	t_job				*ok;

	ok = j->ok;
	while (ok != NULL)
	{
		if (ok->completed == 1)
		{
			if (ok->status == 0 && ok != NULL)
				ok = ok->next;
			else if (ok->status == 0 && ok == NULL)
				return (JC_DONE);
			else
				return (JC_ERR);
		}
		else
			return (JC_RUN);
	}
	return (JC_ERR);
}

int						jc_pipestp(t_job *j)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		if (p->stopped)
			return (1);
		p = p->next;
	}
	return (0);
}

int						jc_status(t_job *j)
{
	int					ret;

	if (j == NULL)
		return (JC_DONE);
	if (j->completed == 0)
		return (jc_pipestp(j) ? JC_STP : JC_RUN);
	else if (j->status == 0)
	{
		if ((ret = get_ok_status(j)) == JC_ERR)
			return (jc_status(j->err));
		else
			return (ret);
	}
	else
		return (jc_status(j->err));
}

int						jc_cpled(t_job *j)
{
	return (j->completed);
}
