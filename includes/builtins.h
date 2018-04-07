/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:10:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/06 19:36:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/param.h>
# include <sys/stat.h>

# include "ft_21sh.h"

# define BU_S_USG ("21sh: usage: set [-+][Fabdfhnolx]")

# define BU_S_HPR ("l: shows local variables. With '+l' shows env beforehand")
# define BU_S_HSE ("o: shows options. '+o' prints it as commands to set them")
# define BU_S_HEX ("a: assignment commands are exported")
# define BU_S_HBG ("b: set job notifications to be immediate")
# define BU_S_HON ("x: prints each action done before execution")
# define BU_S_HFN ("f: inhibit globbing expansion")
# define BU_S_HDO ("d: adds hidden files to globbing")
# define BU_S_HNU ("n: if expansion fails, replace it with a null string")
# define BU_S_HFA ("F: if expansion fails, aborts pipe execution")
# define BU_S_HEL ("h: displays this help. '+h' adds usage beforehand")

# define BU_SET_PRLOC	0x01
# define BU_SET_PRVAR	0x02
# define BU_SET_PRSET	0x04
# define BU_SET_PRCMD	0x08

# define BU_SET_EXPOR	0x01
# define BU_SET_BGCMD	0x02
# define BU_SET_FNEXP	0x04
# define BU_SET_ONCMD	0x08
# define DOTGLOB		0x10
# define NULLGLOB		0x20
# define FAILGLOB		0x40

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
# define SH_ENODIR ("Not a directory")
# define SH_ERIGHT ("Permission denied")
# define SH_EARGTO ("21sh: cd: Too much arguments\n")
# define SH_ENOHOM ("21sh: cd: Variable $HOME not set\n")
# define SH_ENOOPW ("21sh: cd: Variable $OLDPWD not set\n")

# define BU_H_EEMPTY ("121sh: hash empty\n")
# define BU_H_CLR 0x01
# define BH_H_INH 0x02
# define BU_H_DEL 0x04
# define BU_H_PRT 0x08
# define BU_H_LST 0x10

# define BU_H_ETREQU	("21sh: hash: -t: option requires an argument\n")
# define BU_H_EDREQU	("21sh: hash: -d: option requires an argument\n")
# define BU_H_EPREQU	("21sh: hash: -p: option requires two arguments\n")
# define BU_H_ENOKEY	("21sh: hash: %s not found\n")
# define BU_H_USAGE		("21sh: usage: hash [-lr] [-p path] [-dt] [name ...]\n")

# define BU_H_EINVAL ("21sh: hash: -%c: invalid option\n%s")

# define BU_J_L 0x01
# define BU_J_S 0x02
# define BU_J_R 0x04
# define BU_J_P 0x08
# define BU_J_A 0x10

# define EOPT ("invalid option")

# define BU_J_USAGE ("jobs: usage: jobs [-lprs] [jobspec ...]")

# define BU_EX_ENUMARG "21sh: exit: %s: numeric argument required\n"

# define BU_HI_EEORNG "21sh: history, %s: history position out of range\n"

# define BU_E_EARG "21sh: env: option requires an argument -- 'u'\n"
# define BU_E_EINVARG "21sh: env: Cannot unset '%s': Invalid argument\n"
# define BU_E_EINVOPT "221sh: env: invalid option -- '%c'\n"

typedef struct s_ctx	t_ctx;
typedef struct s_proc	t_proc;

int						ft_cd(t_proc *p, t_ctx *ctx);
int						cd_pipeline(t_ctx *ctx, char *path, int opt);
int						remove_prev_dir(char *trim_path, unsigned *i, char *argpath);
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
int						ft_fg(t_proc *proc, t_ctx *ctx, int pipeline);
int						ft_bg(t_proc *proc, t_ctx *ctx, int pipeline);
int						ft_kill(t_proc *proc, t_ctx *ctx, int pipeline);
int						ft_exit(t_proc *p, t_ctx *ctx, int pipeline);
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

void					bu_jobs_print(t_ctx *ctx, size_t i, int flag);
int						bu_jobs_args(t_proc *p);
void					bu_jobs_long(t_ctx *ctx, int flag);

#endif
