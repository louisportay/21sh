/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:15:26 by lportay           #+#    #+#             */
/*   Updated: 2017/11/28 13:13:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_result(char *result, int isok)
{
	ft_putstr(result);
	return (isok);
}

static int	analyse_signal(int status, t_signal *sig)
{
	int i;

	i = 0;
	while (WTERMSIG(status) != sig[i].signum && sig[i].signum)
		i++;
	if (sig[i].signum)
	{
		ft_putstr(RED" [");
		ft_putstr(sig[i].signame);
		return (print_result("]\n"RESET, -1));
	}
	else
	{
		ft_putstr(RED" [Other Sig: ");
		ft_putnbr(WTERMSIG(status));
		return (print_result("]\n"RESET, -1));
	}
	return (print_result(YELLOW" [Unknown Error due to a Signal]\n"RESET, 1));
}

/*
 ** Returns 0 if test succeeded otherwise returns -1
 */

int			exec_test(t_utest *test)
{
	pid_t	pid;
	int 	status;
	t_signal sig[] = {
		{SIGSEGV, "SIGSEGV"},
		{SIGILL, "SIGILL"},
		{SIGABRT, "SIGABRT"},
		{SIGFPE, "SIGFPE"},
		{SIGBUS, "SIGBUS"},
		{SIGPIPE, "SIGPIPE"},
		{SIGTRAP, "SIGTRAP"},
		{0, NULL}
	};
	ft_putstr(test->testname);
	pid = fork();
	if (pid == 0)
		exit(test->testfunc());
	else if (wait(&status) == -1)
		return (print_result(YELLOW" [Wait Error]\n"RESET, -1));
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return (print_result(GREEN" [OK]\n"RESET, 0));
	else if (WIFEXITED(status))
		return (print_result(RED" [KO]\n"RESET, -1));
	else if (WIFSIGNALED(status))
		return (analyse_signal(status, sig));
	return (print_result(YELLOW" [Unknown Error]\n"RESET, 1));
}
