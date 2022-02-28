/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/28 23:54:26 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambigous_file(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type != WRD && tokens[i]->type != PIPE
			&& tokens[i]->type != HRDOC)
		{
			if (ft_strchr(tokens[i + 1]->val, ' '))
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}

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
	if (!syntax_error(tokens))
		write(2, "minishell: syntax error near unexpected token\n", 47);
	else if (g_all.lexer_err == 1)
		write(2, "minishell: quotes left unclosed\n", 33);
	else if (check_ambigous_file(tokens))
		write(2, "BASH: Ambiguous Redirect!\n", 27);
	else
		parse_commands(tokens);
	free_tokens(tokens);
	free(lexer->cmd);
	free(lexer);
}

void	free_rdr(t_redirect *rdr)
{
	t_redirect	*cur;
	t_redirect	*tmp;

	cur = rdr;
	while (cur)
	{
		free(cur->file);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void	free_cmd(void)
{
	t_command	*cur;
	t_command	*tmp;
	int			i;

	if (g_all.cmd == NULL)
		return ;
	cur = g_all.cmd;
	while (cur)
	{
		if (cur->cmd)
			free(cur->cmd);
		i = 0;
		while (cur->args && cur->args[i])
		{
			free(cur->args[i]);
			i++;
		}
		if (cur->args)
			free(cur->args);
		free_rdr(cur->red);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void	execute(t_command *cmd)
{
	open_heredocs(cmd);
	if (!cmd->next && is_builtin(cmd->cmd))
		simple_cmd(cmd);
	else
		complex_cmd(cmd);
	close_heredocs(cmd);
}

void	init_g_all(void)
{
	g_all.lexer_err = 0;
	g_all.ret = 0;
	free_cmd();
	g_all.line = NULL;
	g_all.cmd = NULL;
}

int	main(int argc, char **argv, char **envv)
{
	(void)argv;
	g_all.pids_sig = 0;
	collect_env(envv);
	if (argc == 1)
	{
		while (1)
		{
			init_g_all();
			signal(SIGINT, cntl_c);
			signal(SIGQUIT, SIG_IGN);
			g_all.line = readline("minishell-v1.0$ ");
			if (!check_line())
				exit(0);
			if (g_all.line[0] == '\0')
				continue ;
			add_history(g_all.line);
			parse();
			if (g_all.cmd && !g_all.lexer_err)
				execute(g_all.cmd);
		}
	}
	return (0);
}


/*
 >> eof
*/