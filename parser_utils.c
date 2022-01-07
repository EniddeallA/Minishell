/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 01:44:14 by akhalid           #+#    #+#             */
/*   Updated: 2022/01/06 01:45:34 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_all_quotes(char *line, int *index)
{
	int i;

	i = *index;
	if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
	}
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"' && line[i])
			i++;
	}
	*index = i;
}

int count_pipes(char *line)
{
	int i;
	int n_pipes;

	i = -1;
	n_pipes = 1;
	while (line[++i])
	{
	 	skip_all_quotes(line, &i);
		if (line[i] == '|')
			n_pipes += 1;
	}
	return (n_pipes);
}

int check_line(char *line)
{
	return (1);
}
