/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:36:38 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 16:45:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

# include "ft_astr.h"
# include "ft_hashset.h"
# include "ft_string.h"
# include "ft_stdio.h"
# include "libft.h"
# include "qbuf.h"
# include "stack.h"

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

# define KEY_VAL(KEY, VAL) (t_keyval){.val = VAL, .key = KEY} // ET LA NORME ALORS?

typedef struct	s_keyval
{
	int 		key;
	char 		*val;
}				t_keyval;

#endif
