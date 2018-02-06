/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:32:10 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/05 18:35:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern char **environ;

int main(int ac, char **av)
{
	char		**env;

	env = ft_astr_dup(environ);
	ft21_parse(
}
