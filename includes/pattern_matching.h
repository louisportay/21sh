/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:31:46 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 15:33:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_MATCHING_H
# define PATTERN_MATCHING_H

# include <limits.h>

# include "ft_21sh.h"

# define SPEC_CHR_OP ("*?[|")
# define SPEC_CHR_OP_CNT 4

# define SPEC_CHR ("*?[")
# define SPEC_CHR_CNT 3

# define PM_WORD ("word")
# define PM_ALNUM ("alnum")
# define PM_ALPHA ("alpha")
# define PM_ASCII ("ascii")
# define PM_BLANK ("blank")
# define PM_CNTRL ("cntrl")
# define PM_DIGIT ("digit")
# define PM_GRAPH ("graph")
# define PM_LOWER ("lower")
# define PM_PRINT ("print")
# define PM_PUNCT ("punct")
# define PM_SPACE ("space")
# define PM_UPPER ("upper")
# define PM_XDIGIT ("xdigit")
# define PM_CLASS_WILDCARD (":*****:")

# define PM_LOWER_STR ("abcdefghijklmnopqrstuvwxyz")
# define PM_UPPER_STR ("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
# define PM_DIGIT_STR ("0123456789")
# define PM_PUNCT_STR ("!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~")
# define PM_SPACE_STR (" \t\n\r\f\v")
# define PM_XLOWER_STR ("abcdef")
# define PM_XUPPER_STR ("ABCDEF")

# ifndef NONE
#  define NONE 0
# endif

# define EXTOP 1

enum						e_str_bin
{
	LOWER_BIN = 1 << 0,
	UPPER_BIN = 1 << 1,
	DIGIT_BIN = 1 << 2,
	PUNCT_BIN = 1 << 3,
	SPACE_BIN = 1 << 4,
	XLOWER_BIN = 1 << 5,
	XUPPER_BIN = 1 << 6
};

enum						e_mt_type
{
	FILEN = 1,
	RECUR = 2,
	DIREC = 3,
	ANYSI = 4,
	RANGE = 5,
	RNMOD = 6,
	STRIN = 7,
	MP_CL = 8,
	MP_PI = 9
};

enum						e_modtype
{
	MP_01 = 1,
	MP_0N = 2,
	MP_1N = 3,
	MP_1S = 4,
	MP_EX = 5
};

typedef struct s_mtok		t_mtok;
typedef int					(*t_mptr)(char **matcher, t_mtok **tmp);

typedef union u_mod			t_mod;

union						u_mod
{
	char					*str;
	enum e_modtype			mod;
};

struct						s_mtok
{
	enum e_mt_type			type;
	t_mod					data;
	t_mtok					*next;
};

int							mtok_insert(t_mtok **head, t_mtok **curr,
										t_mtok *tmp);
t_mtok						*mtok_last(t_mtok *tok);
t_mtok						*mtok_create(enum e_mt_type type);
t_mtok						*mtok_create_mod(enum e_mt_type type,
												enum e_modtype mod);
t_mtok						*mtok_create_str(enum e_mt_type type, char *str);
void						mtok_clear(t_mtok **mt);
t_mtok						*mtok_splitstr(t_mtok *o);
void						mtok_print(t_mtok *o);
int							mtok_until_str(t_mtok *tok, char *str,
											t_mtok **next);
t_mtok						*mtok_requal(t_mtok *tok);

char						*get_tok_names(enum e_mt_type id);

char						*create_range(char *beg, char *end);

t_mptr						get_matcher(int id);
int							get_string(char **matcher, t_mtok **tmp);

int							get_matcher_tokens(char *matcher, t_mtok **tmp,
												int flags);

int							match(char *str, t_mtok *tokens);
int							compare(char *str, size_t pos, t_mtok *token);

void						ft_mb_add_unsafe(t_qbuf *buf, char *str);
void						qbuf_addrange(t_qbuf *buf, char beg, char end);
int							ft_strwildcmp(char *str, char *matcher);
char						*ft_strrmdup(char **str);

int							extended_matcher(char *matcher, t_mtok **tokens);

int							match_filename(char **str, t_mtok **token);

#endif
