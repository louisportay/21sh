/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdsub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:09:20 by lportay           #+#    #+#             */
/*   Updated: 2018/04/18 20:04:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_cmdsub.h"

int		expand_cmdsub(char *s, char **new_s, t_ctx *ctx)
{
	(void)ctx;

	char *ptr;
	char *truc_a_subshell;

	if (s[0] == '\'')
		return (0);
	else if (s[0] == '`')
	{
		ptr = ft_strchr(&s[1], '`');
		*ptr = '\0';
		truc_a_subshell = ft_strdup(&s[1]);
//		printf("|%s|\n", truc_a_subshell);
//		fflush(stdout);

		char	buf[BUFF_SIZE];
		t_qbuf	*qbuf;
		int		fd[2];
//		int		backup;
		pid_t	pid;

//		backup = dup(STDOUT_FILENO);
//		ft_dlstprint(sub, "\n", (void (*)(void *))&ft_putstr);
		
		pipe(fd);
		t_dlist *sub = dlst_from_str(truc_a_subshell);
		if (ft_dlstnewaddend(sub, "\n", 1, &ft_dlstnew))
			fatal_err(NOMEM, get_ctxaddr());
		pid = fork();

		if (pid < 0)
			ft_dprintf(STDERR_FILENO, "fork error\n");
		if (pid == 0)
		{
			close(fd[0]);
			close(ctx->std_fd[1]);
			ctx->std_fd[1] = fd[1];
			dup2(fd[1], STDOUT_FILENO);
			exec_loop(sub);
			exit(0);
		}
		else
		{
			close(fd[1]);
			qbuf = qbuf_new(128);

			while (read(fd[0], buf, BUFF_SIZE) != 0)
				qbuf_addn(qbuf, buf, BUFF_SIZE);
			
			qbuf_add(qbuf, ++ptr);
			free(truc_a_subshell);
			*new_s = qbuf_del(&qbuf);
			//printf("|%s|\n", *new_s);
			ft_dlstdel(&sub, &delvoid);
			return (1);

		}






	}
	
	
	
	
	else if ((ptr = ft_strstr(s, "$(")) != NULL)
	{
		if (ptr == s || *(ptr - 1) != '\\')
		{
			if ((ptr = ft_strchr(s, ')')) && *(ptr - 1) != '\\')
				puts("SUCCESS");
		}
	}
	return (0);
}
