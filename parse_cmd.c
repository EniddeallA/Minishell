/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:09:52 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/17 18:47:45 by akhalid          ###   ########.fr       */
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
	(*cmd)->args = NULL;
	(*cmd)->in = NULL;
	(*cmd)->out = NULL;
	(*cmd)->out = NULL;
	(*cmd)->out = NULL;
}

char *env_to_key(char *str, int i)
{
	int j;
	char *key;

	key = (char *)malloc(sizeof(char) * (str[0] - i + 1));
	j = 0;
	while (j < i)
	{
		key[j] = str[j];
		j++;
		i++;
	}
	key[j] = '\0';
	return (key);
}

void expand_command(char *line, t_command **cmd)
{
	int i;
	int start;
	char *key;
	int j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			start = ++i;
			while (line[i] != ' ')
				i++;
			key = env_to_key(&line[start], i);
			j = -1;
			while (j++ < (*cmd)->n_env)
			{
				//IM HERE
			}
		}
	}
}

void	parse_commands(t_command **cmd, char *line)
{
	int n_cmd;
	int i;

	(*cmd)->n_cmd = number_of_commands(line);
	*cmd = (t_command *)malloc(sizeof(t_command) * (n_cmd + 1));
	init_cmd(cmd);
	expand_command(line, cmd);
	i = -1;
	while (++i < (*cmd)->n_cmd)
	{
		// parse_command(line, &cmd[i]);
	}
	return (cmd);
}
