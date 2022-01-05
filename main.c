/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/01/06 00:54:51 by akhalid          ###   ########.fr       */
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

void convert_cmd_to_args(char *cmd, int n_cmd)
{
	int i;
	int j;
	int arg;
	int size;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	j = i;
	size = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || !cmd[i + 1])
			size += 1;
		i++;
	}
	g_all.cmd[n_cmd].n_arg = size;
	g_all.cmd[n_cmd].args = (char **)malloc(sizeof(char *) * (size + 1));
	i = j;
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
	convert_cmd_to_args(cmd, n_cmd);
}

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
		int j = -1;
		while (++j < g_all.cmd[i].n_arg)
			printf("%s\n", g_all.cmd[i].args[j]);
	}
}

int check_line(char *line)
{
	return (1);
}

int main(int argc, char **argv, char **envv)
{
	char *line;
	
	(void)argc;
	(void)argv;
	collect_env(envv);
	while ((line = readline("minishell-v1.0$ ")))
	{
		if (!check_line(line))
			;
		else
		{
			parse_line(line);
			printf("%d\n", g_all.n_cmd);
		}
	}
	return (0);
}
