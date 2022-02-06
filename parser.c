/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:10:57 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/06 01:31:26 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *get_token(t_lexer *lexer)
{
	if (lexer->c && lexer->i < lexer->length)
	{
		if (ft_isspace(lexer->c))
			skip_spaces(lexer);
		if (!is_operator(lexer->c) && lexer->c != '\'' && lexer->c != '\"')
			return (unquoted_wrd_token(lexer));
		if (lexer->c == '\"');
			return (quoted_wrd_token(lexer, lexer->c));
		if (lexer->c == '\'')
			return (quoted_wrd_token(lexer, lexer->c));
		return (operator_token(lexer));
	}
	return (0);
}

void	parser()
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