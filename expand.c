/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:43:42 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/08 03:21:07 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *unquoted_expansion(t_lexer *lexer)
{
	char *key;
	char *val;

	lexer_forward(lexer);
	if (lexer->c == '$' || lexer->c == '\"' || lexer->c == ' ' || lexer->c )
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit_status(lexer));
	key = ft_strdup("");
	while (!is_operator(lexer->c) && !ft_isspace(lexer->c) && lexer->c &&
		lexer->c != '$' && lexer->c != '\'' && lexer->c != '\"')
	{
		val = lexer_to_string(lexer);
		key = ft_strjoin(key, val);
		lexer_forward(lexer);
	}
	val = expand_key(key);
	free(key);
	val = more_expansion(lexer, val);
	return (val);
}

char *quoted_expansion(t_lexer *lexer)
{
	char	*key;
	char	*val;

	lexer_forward(lexer);
	if (lexer->c == '\"' || lexer->c == '$' || lexer->c == ' ')
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit_status(lexer));
	key = ft_strdup("");
	while (lexer->c != '\"' && lexer->c != ' ' && lexer->c != '$' && lexer->c)
	{
		val = lexer_to_string(lexer);
		key = ft_strjoin(key, val);
		lexer_forward(lexer);
	}
	val = expand_key(key);
	free(key);
	if (lexer->c == '$')
		val = ft_strjoin(val, quoted_expansion(lexer));
	return (val);
}
