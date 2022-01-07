/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 01:45:23 by akhalid           #+#    #+#             */
/*   Updated: 2022/01/07 04:48:11 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void convert_cmd_to_args(char *cmd, int n_cmd, int i, int j)
{
	int arg;

	arg = 0;
	while (cmd[j])
	{
		skip_all_quotes(cmd, &j);
		if (cmd[j] == ' '|| !cmd[j + 1])
		{
			if (!cmd[j + 1])
				g_all.cmd[n_cmd].args[arg] = ft_substr(cmd, i, j - i + 1);
			else
				g_all.cmd[n_cmd].args[arg] = ft_substr(cmd, i, j - i);
			arg++;
			i = j + 1;
		}
		j++;
	}
}

void parse_args(char *cmd, int n_cmd)
{
	int i;
	int j;
	int size;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	j = i;
	size = 0;
	while (cmd[i])
	{
		skip_all_quotes(cmd, &i);
		if (cmd[i] == ' ' || !cmd[i + 1])
			size += 1;
		i++;
	}
	g_all.cmd[n_cmd].n_arg = size;
	g_all.cmd[n_cmd].args = (char **)malloc(sizeof(char *) * (size + 1));
	i = j;
	convert_cmd_to_args(cmd, n_cmd, i, j);
}

void parse_command(char **line, int n_cmd)
{
	char *str;
	int i;
	char *cmd;
	int start;

	str = *line;
	i = 0;
	if (str[i] == '|')
		i++;
	while (str[i] == ' ')
		i++;
	start = i;
	while (str[i])
	{
		skip_all_quotes(str, &i);
		if (str[i] == '|')
			break;
		i++;
	}
	*line = &str[i];
	cmd = ft_substr(str, start , i - start);
	parse_args(cmd, n_cmd);
	free(cmd);
}

// void handle_redirection(int i)
// {
// 	int j;

// 	j = -1;
// 	while (++j < g_all.cmd[i].n_arg)
// }

void parse_line(char *line)
{
	int i;

	g_all.n_cmd = count_pipes(line);
	g_all.cmd = (t_command *)malloc(sizeof(t_command) * (g_all.n_cmd));
	i = - 1;
	while (++i < g_all.n_cmd)
	{
		printf("command %d\n", i);
		parse_command(&line, i);
		// int j = -1;
		// while (++j < g_all.cmd[i].n_arg)
		// 	printf("%s\n", g_all.cmd[i].args[j]);
		// expand_variables();
	}
}
