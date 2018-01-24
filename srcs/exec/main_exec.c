/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:45:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/24 17:29:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#define CMD ("ls -l | cat -e")

int main(int ac, char **av)
{
	t_job	*j;
	t_proc	*p[3];

	(void)ac;
	(void)av;
	if ((j = (t_job *)ft_memalloc(sizeof(t_job))) == NULL)
		return (1);
	p[0] = NULL;
	p[2] = proc_new((char *[]){"/bin/ls", "-l", NULL});
	proc_insert(p, p + 1, p[2]);
	p[2] = proc_new((char *[]){"/bin/cat", "-e", NULL});
	proc_insert(p, p + 1, p[2]);
	j = job_new(ft_strdup(CMD), p[0]);
	job_exec(j, 1, 1);
	return (0);
}
