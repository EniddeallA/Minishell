/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:43:42 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/06 03:38:02 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_exit_status(t_lexer *lexer)
{
	lexer_forward(lexer);
	return(ft_itoa(g_all.exit_status));
}

char *more_expansion(t_lexer *lexer, char *tmp)
{
	if (lexer->c == '$')
		tmp = ft_strjoin(tmp, expand_key(lexer));
	if (lexer->c == ' ' && !tmp[0])
		tmp = ft_strjoin(tmp, ft_strdup(" "));
	if (lexer->c == '\'' || lexer->c == '\"')
		tmp = ft_strjoin(tmp, char_quoted_wrd_token(lexer, lexer->c));
	return (tmp);
}

char *unquoted_expansion(t_lexer *lexer)
{
	char *val;
	char *tmp;

	lexer_forward(lexer);
	if (lexer->c == '$' || lexer->c == '\"' || lexer->c == ' ' || lexer->c )
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit_status(lexer));
	val = ft_strdup("");
	while (!is_operator(lexer->c) && !ft_isspace(lexer->c) && lexer->c &&
		lexer->c != '$' && lexer->c != '\'' && lexer->c != '\"')
	{
		tmp = lexer_to_string(lexer);
		val = ft_strjoin(val, tmp);
		lexer_forward(lexer);
	}
	tmp = get_env_val(val);
	free(val);
	tmp = more_expansion(lexer, tmp);
	return (tmp);
}

char *quoted_expansion(t_lexer *lexer)
{
	char	*val;
	char	*tmp;

	lexer_forward(lexer);
	if (lexer->c == '\"' || lexer->c == '$' || lexer->c == ' ')
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit_error(lexer));
	val = ft_strdup("");
	while (lexer->c != '\"' && lexer->c != ' ' && lexer->c != '$' && lexer->c)
	{
		tmp = lexer_to_string(lexer);
		val = ft_strjoin(val, tmp);
		lexer_forward(lexer);
	}
	tmp = get_env_val(val);
	free(val);
	if (lexer->c == '$')
		tmp = ft_strjoin(tmp, quoted_expansion(lexer));
	return (tmp);
}