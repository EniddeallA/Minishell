/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:10:57 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/23 13:54:19 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**realloc_tokens(t_token **tokens, t_token *tmp)
{
	int i;
	t_token **new;

	i = 0;
	if (tokens)
		while (tokens[i])
			i++;
	new = (t_token **)malloc(sizeof(t_token *) * (i + 2));
	i = 0;
	if (tokens)
		while (tokens[i])
		{
			new[i] = (t_token *)malloc(sizeof(t_token));
			new[i]->val = ft_strdup(tokens[i]->val);
			new[i]->type = tokens[i]->type;
			i++;
		}
	new[i++] = tmp;
	new[i] = NULL;
	free_tokens(tokens);
	return (new);
}

t_token *get_token(t_lexer *lexer)
{
	if (lexer->c && lexer->i < lexer->length)
	{
		if (ft_isspace(lexer->c))
			skip_spaces(lexer);
		if (!is_operator(lexer->c) && lexer->c != '\'' && lexer->c != '\"')
			return (unquoted_wrd_token(lexer));
		if (lexer->c == '\"')
			return (quoted_wrd_token(lexer, lexer->c));
		if (lexer->c == '\'')
			return (quoted_wrd_token(lexer, lexer->c));
		return (operator_token(lexer));
	}
	return (0);
}

void	free_tokens(t_token **tokens)
{
	int i;
	
	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			free(tokens[i]->val);
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
}

void parse_commands(t_token **tokens)
{
	t_command *cmd;
	int i;

	g_all.cmd = init_command();
	cmd = g_all.cmd;
	i = 0;
	while (tokens[i])
	{
		token_to_cmd(tokens, cmd, i);
		if (tokens[i]->type == INP || tokens[i]->type == OUT ||
			tokens[i]->type == APND || tokens[i]->type == HRDOC)
			i++;
		if (tokens[i]->type == PIPE)
		{
			cmd->next = init_command();
			cmd = cmd->next;
		}
		i++;
	}
}

int syntax_error(t_token **token)
{
	if (!token)
		return (1);
	return (0);
}

void	parse()
{
	t_lexer *lexer;
    t_token **tokens;
	t_token *tmp;

    lexer = init_lexer();
    tokens = (t_token **)malloc(sizeof(t_token *));
	tokens[0] = NULL;
	while ((tmp = get_token(lexer)))
		tokens = realloc_tokens(tokens, tmp);
	if (syntax_error(tokens))
		write(2, "minishell: syntax error near unexpected token\n", 47);
	else if (g_all.lexer_err == 1)
		write(2, "minishell: quotes left unclosed\n", 33);
	else
		parse_commands(tokens);
	free_tokens(tokens);
	free(lexer);
}
