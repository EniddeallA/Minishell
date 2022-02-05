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
	lexer->content = g_all.line;
	lexer->i = 0;
	lexer->c = g_all.line[0];
	return (lexer);
}

void	parse_line()
{
	t_lexer *lexer;
    t_token **tokens;

    lexer = init_lexer();
    tokens = (t_token **)malloc(sizeof(t_token *) * 2);
	
}