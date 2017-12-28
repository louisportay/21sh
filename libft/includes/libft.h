/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:21:40 by lportay           #+#    #+#             */
/*   Updated: 2017/12/22 11:21:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# define BUFF_SIZE 512
# define RESET			"\e[0m"
# define BOLD			"\e[1m"
# define ITALIC			"\e[3m"
# define STRIKETHROUGH	"\e[9m"
# define BLACK			"\e[30m"
# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define YELLOW			"\e[33m"
# define BLUE			"\e[34m"
# define MAGENTA		"\e[35m"
# define CYAN			"\e[36m"
# define LIGHT_GRAY		"\e[37m"
# define DEFAULT		"\e[39m"
# define DARK_GRAY		"\e[90m"
# define LIGHT_RED		"\e[91m"
# define LIGHT_GREEN	"\e[92m"
# define LIGHT_YELLOW	"\e[93m"
# define LIGHT_BLUE		"\e[94m"
# define LIGHT_MAGENTA	"\e[95m"
# define LIGHT_CYAN		"\e[96m"
# define WHITE			"\e[97m"
# include "ft_stdio.h"
# include "ft_stdlib.h"
# include "ft_string.h"
# include "ft_ctype.h"
# include "ft_wchar.h"
# include "buffer.h"
# include "ft_dlst.h"
# include "ft_lst.h"
# include "other.h"
# include "ft_hash.h"
# include "ft_btree.h"
# include "utest.h"
# include "stack.h"

# define KEY_VAL(KEY, VAL) (t_keyval){.val = VAL, .key = KEY}

/*
** The 'val' field is first because of padding
*/

typedef struct	s_keyval
{
	char 		*val;
	int 		key;
}				t_keyval;

#endif
