/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:09:52 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/16 11:37:25 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int number_of_commands(char *line)
{
	int n_cmd;
	int i;

	i = 0;
	n_cmd = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
		}
		if (line[i] == '|')
			n_cmd++;
		i++;
	}
	return (n_cmd);
}

void init_cmd(t_command **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->args = NULL;
}

void parse_command(t_command *cmd)
{
	
}

t_command *parse_commands(char *line, t_env *env)
{
	t_command *cmd;
	int n_cmd;
	int i;

	n_cmd = number_of_commands(line);
	cmd = (t_command *)malloc(sizeof(t_command) * (n_cmd + 1));
	init_cmd(&cmd);
	i = -1;
	while (++i < n_cmd)
	{
		parse_command(&cmd[i]);
		// HERE
	}	
	
	return (cmd);
}