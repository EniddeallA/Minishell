/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/10 16:05:09 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envv)
{
	(void)argv;
	collect_env(envv);
	if (argc == 1)
		while (1)
		{
			g_all.line = readline("minishell-v1.0$ ");
			if (!check_line())
				exit(0);
			parser();
			int i = 0;
			while (g_all.cmd)
			{
				while (g_all.cmd->args[i])
				{
					printf("%s\n", g_all.cmd->args[i]);
					i++;
				}
				g_all.cmd = g_all.cmd->next;
			}
			/*
				**	Execute
			*/
		}	
	
	return (0);
}
