/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/17 01:12:27 by akhalid          ###   ########.fr       */
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
			signal(SIGINT, cntl_c);
			signal(SIGQUIT, SIG_IGN);
			g_all.line = readline("minishell-v1.0$ ");
			if (!check_line())
				exit(0);
			if (g_all.line[0] == '\0')
				continue;
			add_history(g_all.line);
			parse();
			int i;
			while (g_all.cmd)
			{
				i = 0;
				while (g_all.cmd->args[i])
				{
					printf("%s ", g_all.cmd->args[i]);
					i++;
				}
				printf("\n");
				g_all.cmd = g_all.cmd->next;
			}
			if (g_all.cmd && !g_all.lexer_err)
				execute(g_all.cmd);
		}	
	
	return (0);
}


//echo '"'$USER'"'
//echo $U?SER