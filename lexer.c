/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:10:29 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/06 02:07:16 by akhalid          ###   ########.fr       */
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

void	lexer_backward(t_lexer *lexer)
{
	if (lexer->i > 0)
	{
		lexer->i -= 1;
		lexer->c = lexer->cmd[lexer->i];
	}
}

char *lexer_to_string(t_lexer *lexer)
{
	char *s;

	s = (char *)malloc(sizeof(char) * 2);
	s[0] = lexer->c;
	s[1] = '\0';
	return (s);
}
