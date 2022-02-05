/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:31:59 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/02 01:32:13 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer()
{
	t_lexer *lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	lexer->cmd = g_all.line;
	lexer->i = 0;
	lexer->c = g_all.line[0];
	lexer->length = ft_strlen(lexer->cmd);
	return (lexer);
}

void	lexer_forward(t_lexer *lexer)
{
	if (lexer->c && lexer->i < lexer->length)
	{
		lexer->i += 1;
		lexer->c = lexer->cmd[lexer->i];
	}
}

t_token *init_token(t_type type, char *val)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	token->val = val;
	token->type = type;
	return (token);
}

char *lexer_to_string(t_lexer *lexer)
{
	char *s;

	s = (char *)malloc(sizeof(char) * 2);
	s[0] = lexer->c;
	s[1] = '\0';
	return (s);
}

t_token *token_lf(t_lexer *lexer, t_token *token)
{
	lexer_forward(lexer);
	return (token);
}

t_token *operator_token(t_lexer *lexer)
{
	if (lexer->c == '|')
		return (token_lf(lexer, init_token(PIPE, lexer_to_string(lexer))));
	if (lexer->c == '>')
	{
		lexer_forward(lexer);
		if (lexer->c == '>')
			return (token_lf(lexer, init_token(APND, lexer_to_string(lexer))));
		return(init_token(OUT, lexer_to_string(lexer)));
	}
	if (lexer->c == '<')
	{
		lexer_forward(lexer);
		if (lexer->c == '<')
			return (token_lf(lexer, init_token(HEREDOC, lexer_to_string(lexer))));
		return(init_token(INP, lexer_to_string(lexer)));
	}
	return (NULL);
}

t_token *unquoted_wrd_token(t_lexer *lexer)
{
	char *val;

	while (!is_operator(lexer->c) && !ft_isspace(lexer->c) && lexer->c)
	{
		if (lexer->c == '$')
			

	}
	return (init_token(WRD, val));
}

t_token *get_token(t_lexer *lexer)
{
	if (lexer->c && lexer->i < lexer->length)
	{
		if (ft_isspace(lexer->c))
			skip_spaces(lexer);
		if (!is_operator(lexer->c) && lexer->c != '\'' && lexer->c != '\"')
			return (unquoted_wrd_token(lexer));
		if (lexer->c == '\"');
			return (quoted_wrd_token(lexer));
		if (lexer->c == '\'')
			return (quoted_wrd_token(lexer));
		return (operator_token(lexer));
	}
	return (0);
}

void	parse_line()
{
	t_lexer *lexer;
    t_token **tokens;
	t_token *tmp;

    lexer = init_lexer();
    tokens = (t_token **)malloc(sizeof(t_token *));
	tokens[0] = NULL;
	while ((tmp = get_token(lexer)))
		tokens = realloc_tokens(tokens, tmp);
}