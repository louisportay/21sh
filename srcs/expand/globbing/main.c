#include <fcntl.h>
#include <stdio.h>
#include "globbing.h"
#include <string.h>

static void		print_list(t_list *lst)
{
	char		*str;

	while (lst != NULL)
	{
		str = (char *)lst->content;
		write(STDOUT_FILENO, str, strlen(str));
		lst = lst->next;
	}
}

static void		test(char *str, int id)
{
	int			fd;
	int			bu_stdout;
	char		*ret;
	char		*filename;
	char		*command;
	t_ctx		ctx;

	bzero(&ctx, sizeof(t_ctx));
	bu_stdout = dup(STDOUT_FILENO);
	asprintf(&filename, "test_%d_system", id);
	fd = open(filename, O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	asprintf(&command, "echo %s", str);
	system(command);
	free(command);
	asprintf(&filename, "test_%d_user", id);
	fd = open(filename, O_WRONLY);
	expand_glob(str, &ret, &ctx);
	write(fd, ret, strlen(ret));
	close(fd);
	free(ret);
	dup2(bu_stdout, STDOUT_FILENO);
	close(bu_stdout);
}

int				main(void) {
	test("*", 0);
//	test("./*");
	return (0);
}
