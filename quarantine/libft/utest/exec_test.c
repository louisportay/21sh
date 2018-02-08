/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:15:26 by lportay           #+#    #+#             */
/*   Updated: 2017/12/12 19:35:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_result(char *result, int ret)
{
	ft_putstr(result);
	return (ret);
}

static void	init_keyval(t_keyval *sig)
{
	sig[0] = KEY_VAL(SIGSEGV, "SIGSEGV");
	sig[1] = KEY_VAL(SIGILL, "SIGILL");
	sig[2] = KEY_VAL(SIGABRT, "SIGABRT");
	sig[3] = KEY_VAL(SIGFPE, "SIGFPE");
	sig[4] = KEY_VAL(SIGBUS, "SIGBUS");
	sig[5] = KEY_VAL(SIGPIPE, "SIGPIPE");
	sig[6] = KEY_VAL(SIGTRAP, "SIGTRAP");
	sig[7] = KEY_VAL(0, NULL);
}

static int	analyse_signal(int status)
{
	t_keyval	sig[8];
	int			i;

	i = 0;
	init_keyval(sig);
	while (WTERMSIG(status) != sig[i].key && sig[i].key)
		i++;
	if (sig[i].key)
	{
		ft_putstr(RED" [");
		ft_putstr(sig[i].val);
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
		return (analyse_signal(status));
	return (print_result(YELLOW" [Unknown Error]\n"RESET, 1));
}
