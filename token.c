/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:10:55 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/10 15:14:43 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *init_token(t_type type, char *val)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	token->val = val;
	token->type = type;
	return (token);
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
		if (lexer->cmd[lexer->i + 1] == '>')
			return (token_lf(lexer, init_token(APND, lexer_to_string(lexer))));
		return(token_lf(lexer,init_token(OUT, lexer_to_string(lexer))));
	}
	if (lexer->c == '<')
	{
		if (lexer->cmd[lexer->i + 1] == '<')
			return (token_lf(lexer, init_token(HRDOC, lexer_to_string(lexer))));
		return(token_lf(lexer, init_token(INP, lexer_to_string(lexer))));
	}
	return (NULL);
}

t_token *quoted_wrd_token(t_lexer *lexer, char c)
{
	char *val;
	char *s;

	val = ft_strdup("");
	lexer_forward(lexer);
	while (lexer->c != c && lexer->c)
	{
		if (lexer->c == '$' && c == '\"')
		{
			s = quoted_expansion(lexer);
			lexer_backward(lexer);
		}
		else
			s = lexer_to_string(lexer);
		val = ft_strjoin(val, s);
		lexer_forward(lexer);
	}
	if (lexer->c != c)
		g_all.lexer_err = 1;
	lexer_forward(lexer);
	if (!is_operator(lexer->c) && !ft_isspace(lexer->c) && lexer->c)
		val = more_wrd_token(lexer, val);
	return (init_token(WRD, val));
}

t_token *unquoted_wrd_token(t_lexer *lexer)
{
	char *val;
	char *s;

	val = ft_strdup("");
	while (!is_operator(lexer->c) && !ft_isspace(lexer->c) && lexer->c)
	{
		if (lexer->c == '\'' || lexer->c == '\"')
		{
			val = ft_strjoin(val, char_quoted_wrd_token(lexer,lexer->c));
			break;
		}
		else if (lexer->c == '$')
		{
			s = unquoted_expansion(lexer);
			lexer_backward(lexer);
		}
		else
			s = lexer_to_string(lexer);
		val = ft_strjoin(val, s);
		lexer_forward(lexer);
	}
	if (!val[0])
	{
		free(val);
		return (0);
	}
	return (init_token(WRD, val));
}
