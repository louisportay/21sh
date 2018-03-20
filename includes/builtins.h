/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:10:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/20 16:59:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/param.h>
# include <sys/stat.h>

# include "ft_21sh.h"

# define BU_S_USG ("21sh: usage: set [-+][Fabdfhnolx]")

# define BU_S_HPR ("l: displays local variables. With '+l' shows env beforehand")
# define BU_S_HSE ("o: displays options. '+o' prints it as commands to set them")
# define BU_S_HEX ("a: assignment commands are exported")
# define BU_S_HBG ("b: set job notifications to be immediate")
# define BU_S_HON ("x: prints each action done before execution")
# define BU_S_HFN ("f: inhib globbing expansion")
# define BU_S_HDO ("d: adds hidden files to globbing")
# define BU_S_HNU ("n: if expansion fails, replace it with a null string")
# define BU_S_HFA ("F: if expansion fails, abords pipe execution")
# define BU_S_HEL ("h: displays this help. '+h' adds usage beforehand")

# define BU_SET_PRLOC (1 << 0)
# define BU_SET_PRVAR (1 << 1)
# define BU_SET_PRSET (1 << 2)
# define BU_SET_PRCMD (1 << 3)

# define BU_SET_EXPOR (1 << 0)
# define BU_SET_BGCMD (1 << 1)
# define BU_SET_FNEXP (1 << 2)
# define BU_SET_ONCMD (1 << 3)
# define DOTGLOB (1 << 4)
# define NULLGLOB (1 << 5)
# define FAILGLOB (1 << 6)

# define BU_SET_ON ("\ton\n")
# define BU_SET_OFF ("\toff\n")
# define BU_SET_MEXPO ("allexport")
# define BU_SET_MBGCM ("notify")
# define BU_SET_MFNEX ("noglob")
# define BU_SET_MONCM ("xtrace")
# define BU_SET_GLDOT ("dotglob")
# define BU_SET_GLNUL ("nullglob")
# define BU_SET_GLFAI ("failglob")

# define SH_EWFMT ("setenv: Wrong format: <key>=<value> - ")
# define SH_ENKEY ("setenv: Missing key: ")

# define SH_ECHO ("echo")
# define SH_CD__ ("cd")
# define SH_SETE ("setenv")
# define SH_UNSE ("unsetenv")
# define SH_ENV_ ("ctx")
# define SH_PENV ("printenv")
# define SH_EXIT ("exit")

# define SH_ENOFOD ("No such file or directory")
# define SH_ERIGHT ("Permission denied")
# define SH_EARGTO ("221sh: cd: Too much arguments\n")
# define SH_ENOHOM ("221sh: cd: Variable $HOME not set\n")
# define SH_ENOOPW ("221sh: cd: Variable $OLDPWD not set\n")

# define BU_H_EEMPTY ("121sh: hash empty\n")
# define BU_H_CLR (1 << 0)
# define BH_H_INH (1 << 1)
# define BU_H_DEL (1 << 2)
# define BU_H_PRT (1 << 3)
# define BU_H_LST (1 << 4)

# define BU_H_ETREQU ("221sh: hash: -t: option requires an argument\n")
# define BU_H_EDREQU ("221sh: hash: -d: option requires an argument\n")
# define BU_H_EPREQU ("221sh: hash: -p: option requires two arguments\n")
# define BU_H_USAGE_ ("21sh: usage: hash [-lr] [-p path] [-dt] [name ...]\n")

# define BU_H_EINVAL ("221sh: hash: -%c: invalid option\n%s")

typedef struct s_ctx	t_ctx;
typedef struct s_proc	t_proc;

int						ft_cd(t_proc *p, t_ctx *ctx);
int						ft_echo(t_proc *p, t_ctx *ctx);
int						ft_printenv(t_proc *p, t_ctx *ctx);
int						ft_setenv(t_proc *p, t_ctx *ctx);
int						ft_export(t_proc *p, t_ctx *ctx);
int						ft_unsetenv(t_proc *proc, t_ctx *ctx);
int						ft_unset(t_proc *proc, t_ctx *ctx);
int						ft_hash(t_proc *proc, t_ctx *ctx);
int						ft_set(t_proc *proc, t_ctx *ctx);
int						ft_env(t_proc *p);
int						ft_history(t_proc *p, t_ctx *ctx);
int						ft_jobs(t_proc *proc, t_ctx *ctx);
int						ft_fg(t_proc *proc, t_ctx *ctx);
int						ft_bg(t_proc *proc, t_ctx *ctx);
int						ft_kill(t_proc *proc, t_ctx *ctx);
int						ft_exit(t_proc *p, t_ctx *ctx);
int						modenv(t_proc *p, t_ctx *ctx, char *name);
int						bu_hash_getopts(t_proc *p, t_ctx *ctx, int *i);
int						bu_set_getopts(t_proc *p, t_ctx *ctx, int i);
int						is_identifier(char *str);
int						is_sane(char *str, int *end);
int						env_i_opt(t_proc *p);
int						env_u_opt(t_proc *p);
int						env_invalid_opt(t_proc *p);
int						env_assignment(t_proc *p, int *getopt, char *eq_pos);
int						dash_opt(int *getopt);

#endif
