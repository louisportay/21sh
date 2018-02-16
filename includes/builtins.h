/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:10:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/16 18:08:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/param.h>
# include <sys/stat.h>

# include "ft_21sh.h"

# define SH_EWFMT ("setenv: Wrong format: <key>=<value> - ")
# define SH_ENKEY ("setenv: Missing key: ")

# define SH_ECHO ("echo")
# define SH_CD__ ("cd")
# define SH_SETE ("setenv")
# define SH_UNSE ("unsetenv")
# define SH_ENV_ ("ctx")
# define SH_PENV ("printenv")
# define SH_EXIT ("exit")

# define SH_ENOFOD ("cd: No such file or directory\n")
# define SH_ERIGHT ("cd: Permission denied\n")
# define SH_EARGTO ("cd: Too much arguments\n")
# define SH_ENOHOM ("cd: Variable $HOME not set\n")
# define SH_ENOOPW ("cd: Variable $OLDPWD not set\n")

typedef struct s_ctx	t_ctx;
typedef struct s_proc	t_proc;

int						ft_cd(char **args, t_ctx *ctx);
int						ft_echo(t_proc *p, t_ctx *ctx);
int						ft_exit(char **args, t_ctx *ctx);
int						ft_env(char **args, t_ctx *ctx);
int						ft_printenv(char **args, t_ctx *ctx);
int						ft_setenv(char **argv, t_ctx *ctx);
int						ft_unsetenv(char **argv, t_ctx *ctx);
int						ft_hash(t_proc *proc, t_ctx *ctx);

#endif
