/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 04:45:31 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/25 02:14:20 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths()
{
	char *value;
	char **paths;

	value = get_env_value("PATH");
	if (!value)
		return (0);
	paths = ft_split(value, ':');
	return (paths);
}

char	*concatenate(char *str, char *cmd, char *path)
{
	str = ft_strdup(path);
	str = ft_strjoin(str, ft_strdup("/"));
	str = ft_strjoin(str, ft_strdup(cmd));
	return (str);
}

char	*free_paths(char **paths, char *str, int ret)
{
	int i;
	
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	if (str && !ret)
	{
		free(str);
		return (0);
	}
	else if (str && ret)
		return (str);
	return (0);
}

char *get_path(char *cmd)
{
	char **paths;
	int i;
	char *str;
	int ret;

	paths = get_paths();
	if (!paths)
		return (cmd);
	if (!cmd)
		return (0);
	i = -1;
	while (paths[++i])
	{
		str = concatenate(str, cmd, paths[i]);
		ret = open(str, O_RDONLY);
		if (ret != -1)
			return (free_paths(paths, str, 1));
		free(str);
	}
	str = ft_strdup(cmd);
	ret = open(str, O_RDONLY);
	if (ret != -1)
		return (free_paths(paths, str, 1));
	return (free_paths(paths, str, 0));
}

void check_exec(char *path)
{
	struct stat buf;

	if (stat(path, &buf) && S_ISDIR(buf.st_mode))
	{
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", ft_strlen(": is a directory\n"));
		exit(126);
	}
}

void	exec_ve(t_command *cmd)
{
	char *path;

	path = get_path(cmd->cmd);
	if (path)
	{
		check_exec(path);
		execve(path, cmd->args, g_all.env_arr);
		perror(path);
		write(2, "\n", 1);
		exit(126);
	}
	else
	{
		if (errno == 13)
			exit(126);
		if (cmd->cmd)
		{
			write(2, cmd->cmd, ft_strlen(cmd->cmd));
			write(2, ": command not found\n", ft_strlen(": command not found\n"));
		}
	}
}

void execute_cmd(t_command *cmd)
{
	if (!cmd)
		exit(0);
	if (is_builtin(cmd->cmd))
		execute_builtins(cmd);
	else
		exec_ve(cmd);
	exit(0);
}