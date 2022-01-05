/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2022/01/05 02:06:25 by akhalid          ###   ########.fr       */
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

void parse_command(char **line, int n_cmd)
{
	int i;
	int j;
	int start;
	char *str;

	i = -1;
	g_all.n_arg = 1;
	str = *line;
	while (str[++i] && str[i] != '|')
	{
		skip_all_quotes(str, &i);
		if (str[i] == ' ' && str[i + 1] != '|')
			g_all.n_arg += 1;
	}
	g_all.cmd[n_cmd].args = (char **)malloc(sizeof(char *) * (g_all.n_arg + 1));
	j = -1;
	i = 0;
	while (++j < g_all.n_arg)
	{
		start = i;
		while (str[i] && str[i] != '|')
		{
			skip_all_quotes(str, &i);
			if (str[i] == ' ' || !str[i + 1])
			{
				if (!str[i + 1])
					i++;
				g_all.cmd[n_cmd].args[j] = ft_substr(str, start, i - start);
				i++;
				break;
			}
			i++;
		}
	}
	g_all.cmd[n_cmd].args[j] = "\0";
	*line = &str[i];
}
// cmd1 | cmd2

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
		int j = 0;
		while (j < g_all.n_arg)
			printf("|%s|\n", g_all.cmd[i].args[j++]);
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
