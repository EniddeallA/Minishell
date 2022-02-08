/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 22:44:52 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/08 00:27:58 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_exit_status(t_lexer *lexer)
{
	lexer_forward(lexer);
	return(ft_itoa(g_all.exit_status));
}

char *get_env_value(char *key)
{
	t_env *env;

	if (!key)
		return (0);
	env = g_all.env;
	while (env->next)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	if (!ft_strcmp(env->key, key))
		return (env->value);
	return (0);
}

char	*expand_key(char *key)
{
	char *val;

	val = get_env_value(key);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

char *more_expansion(t_lexer *lexer, char *tmp)
{
	if (lexer->c == '$')
		tmp = ft_strjoin(tmp, unquoted_expansion(lexer));
	if (lexer->c == ' ' && !tmp[0])
		tmp = ft_strjoin(tmp, ft_strdup(" "));
	if (lexer->c == '\'' || lexer->c == '\"')
		tmp = ft_strjoin(tmp, char_quoted_wrd_token(lexer, lexer->c));
	return (tmp);
}
