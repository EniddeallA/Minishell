/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/01/06 02:12:06 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envv)
{
	char *line;
	
	(void)argc;
	(void)argv;
	collect_env(envv);
	while ((line = readline("minishell-v1.0$ ")))
	{
		if (!check_line(line))
			;
		else
		{
			parse_line(line);
			printf("%d\n", g_all.n_cmd);
		}
	}
	return (0);
}
