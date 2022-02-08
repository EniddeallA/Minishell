/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:31:59 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/02 01:32:13 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *more_wrd_token(t_lexer *lexer, char *val)
{
	if (lexer->c == '\'' || lexer->c == '\"')
		return (ft_strjoin(val, char_quoted_wrd_token(lexer, lexer->c)));
	else
		return (ft_strjoin(val, char_unquoted_wrd_token(lexer)));
}

char *char_quoted_wrd_token(t_lexer *lexer, char c)
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
	return (val);
}

char *char_unquoted_wrd_token(t_lexer *lexer)
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
			s = quoted_expansion(lexer);
			lexer_backward(lexer);
		}
		else
			s = lexer_to_string(lexer);
		val = ft_strjoin(val, s);
		lexer_forward(lexer);
	}
	if (val[0])
	{
		free(val);
		return (0);
	}
	return (val);
}