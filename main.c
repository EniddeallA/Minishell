/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/28 01:52:06 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(void)
{
	t_lexer	*lexer;
	t_token	**tokens;
	t_token	*tmp;

	lexer = init_lexer();
	tokens = (t_token **)malloc(sizeof(t_token *));
	tokens[0] = NULL;
	tmp = get_token(lexer);
	while (tmp)
	{
		tokens = realloc_tokens(tokens, tmp);
		tmp = get_token(lexer);
	}
	if (syntax_error(tokens))
		write(2, "minishell: syntax error near unexpected token\n", 47);
	else if (g_all.lexer_err == 1)
		write(2, "minishell: quotes left unclosed\n", 33);
	else
		parse_commands(tokens);
	free_tokens(tokens);
	free(lexer);
}

void	execute(t_command *cmd)
{
	open_heredocs(cmd);
	if (!cmd->next && is_builtin(cmd->cmd))
		simple_cmd(cmd);
	else
		complex_cmd(cmd);
	g_all.forked = 0;
	close_heredocs(cmd);
}

int	main(int argc, char **argv, char **envv)
{
	(void)argv;
	collect_env(envv);
	if (argc == 1)
	{
		while (1)
		{
			signal(SIGINT, cntl_c);
			signal(SIGQUIT, cntl_bslash);
			g_all.line = readline("minishell-v1.0$ ");
			if (!check_line())
				exit(0);
			if (g_all.line[0] == '\0' || is_all_spaces(g_all.line))
				continue ;
			add_history(g_all.line);
			parse();
			if (g_all.cmd && !g_all.lexer_err)
				execute(g_all.cmd);
		}
	}	
	return (0);
}
