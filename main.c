/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/17 07:16:09 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_all_spaces(char *s)
{
	int i;

	i = 0;
	while (ft_isspace(s[i]) && s[i])
		i++;
	if (!s[i])
		return (1);
	return (0);
}

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
			if (g_all.line[0] == '\0' || is_all_spaces(g_all.line))
				continue;
			add_history(g_all.line);
			parse();
			if (g_all.cmd && !g_all.lexer_err)
				execute(g_all.cmd);
		}		
	return (0);
}
