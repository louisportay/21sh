#include "ft_21sh.h"

void					jc_updateproc(t_job *j, t_proc *p, int status)
{
	if (WIFEXITED(status))
	{
		p->completed = 1;
		p->status = WEXITSTATUS(status);
	}
	else if (WIFSTOPPED(status))
	{
		p->stopped = 1;
	}
	else if (WIFSIGNALED(status))
	{
		p->completed = 1;
		j->parent->status = WTERMSIG(status);
		dprintf(STDERR_FILENO, "%d: Terminated by signal %d.\n", (int)p->pid, 
				j->parent->status);
        j->parent->done = 1;
	}
}

void					jc_updatepipe(t_job *j)
{
	t_proc				*p;
	pid_t				pid;
	int					status;

	j->completed = 1;
	p = j->procs;
	while (p != NULL)
	{
		if (p->stopped && (j->stopped = 1))
			return ;
		else if (p->completed == 0
					&& (pid = waitpid(p->pid, &status, WNOHANG)) > 0)
			j->completed &= p->completed;
		else if (pid == -1)
		{	/*	THIS HAS TO BE SOMEHOW HANDLED OR UNDERSTOOD	*/	}
		if (p->stopped && (j->stopped = 1))
			return ;
		if (p->next == NULL && j->completed)
			j->status = p->status;
		p = p->next;
	}
}

void					jc_updatejob(t_ctx *ctx, size_t i, t_job *j)
{
	if ((j->status == 0 && j->ok == NULL)
		|| (j->status != 0 && j->err == NULL))
	{
		if (j->parent->bg == 0)
			ctx->fg_job = j->parent;
		else
			ctx->bg_jobs[i] = j->parent;
		j->parent->done = 1;
	}
	else if (j->status == 0)
	{
		if (j->parent->bg == 0)
			ctx->fg_job = j->ok;
		else
			ctx->bg_jobs[i] = j->ok;
	}
	else
	{
		if (j->parent->bg == 0)
			ctx->fg_job = j->err;
		else
			ctx->bg_jobs[i] = j->err;
	}
}

/*
**	MIGHT CAUSE DATA CONCURRENCY
*/
void					jc_updateall(t_ctx *ctx)
{
	size_t				i;

	if (ctx->fg_job != NULL)
		jc_updatepipe(ctx->fg_job);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
		{
			jc_updatepipe(ctx->bg_jobs[i]);
			if (ctx->bg_jobs[i]->completed)
			{
				jc_updatejob(ctx, i, ctx->bg_jobs[i]);
				if (ctx->bg_jobs[i]->parent->done == 0)
					job_exec(ctx->bg_jobs[i], 1, ctx);
			}
		}
		i++;
	}
}

void				jc_signal(int signo)
{
	if (signo != SIGCHLD)
		return ;
	jc_updateall(get_ctxaddr(NULL));
}
