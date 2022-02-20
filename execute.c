/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:03:54 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/20 03:52:03 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_builtins(t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "pwd"))	
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env();
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd->args);
}

int	create_file(t_redirect *red)
{
	int fd;

	fd = -1;
	if (red->type == INP)
		fd = open(red->file, O_RDONLY, 0644);
	else if (red->type == OUT || red->type == APND)
		fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

void redirect_file(t_redirect *red)
{
	int tmp_fd;
	t_redirect *curr;

	curr = red;
	while (curr)
	{
		tmp_fd = curr->fd;
		if (curr->type == OUT || curr->type == APND)
			tmp_fd = dup2(curr->fd, 1);
		else
			tmp_fd = dup2(curr->fd, 0);
		close(curr->fd);
		curr = curr->next;
	}
}

void redirect(t_command *cmd)
{
	t_redirect *red;

	red = cmd->red;
	while (red)
	{
		if (red->type != HRDOC)
			red->fd = create_file(red);
		if (red->fd == -1)
		{
			g_all.exit_status = 1;
			g_all.ret = 1;
			return ;
		}
		red = red->next;
	}
	redirect_file(cmd->red);
}

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
	if (!cmd[0])
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
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ": command not found\n", ft_strlen(": command not found\n"));
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

void simple_cmd(t_command *cmd)
{
	int inp;
	int outp;

	
	inp = dup(0);
	outp = dup(1);
	redirect(cmd);
	execute_builtins(cmd);
	dup2(inp, 0);
	dup2(outp, 1);
	close(inp);
	close(outp);
}

void single_cmd(t_command *cmd, t_pipe *p)
{
	p->pid = fork();
	p->last_pid = p->pid;
	if (!p->pid)
	{
		redirect(cmd);
		execute_cmd(cmd);
	}
	close(p->inp);
	close(p->outp);
}

void multiple_cmds(t_command *cmd, t_pipe *p)
{
	pipe(p->pipe);
	close(p->outp);
	p->outp = p->pipe[1];
	p->pid = fork();
	if (!p->pid)
	{
		dup2(p->outp, 1);
		close(p->pipe[1]);
		dup2(p->inp, 0);
		close(p->pipe[0]);
		redirect(cmd);
		execute_cmd(cmd);
	}
	if (p->inp > 2)
		close(p->inp);
	p->inp = p->pipe[0];
	close(p->outp);
}

void last_cmd(t_command *cmd, t_pipe *p)
{
	p->pid = fork();
	p->last_pid = p->pid;
	if (!p->pid)
	{
		if (p->inp)
			dup2(p->inp, 0);
		if (p->inp)
			close(p->inp);
		redirect(cmd);
		execute_cmd(cmd);
	}
	if (p->pipe[1] != 1)
		close(p->pipe[1]);
	if (p->inp)
		close(p->inp);
}

void	waiting_sigs(t_pipe *p)
{
	g_all.pids_sig = 42;
	waitpid(p->last_pid, &p->last_state, 0);
	while (waitpid(-1, &p->state, 0) > 0)
		;
	if (WIFEXITED(p->last_state))
		g_all.exit_status = WEXITSTATUS(p->last_state);
	else if (WIFSIGNALED(p->last_state))
	{
		if (WTERMSIG(p->last_state) == SIGQUIT)
			write(2, "\\Quit: 3\n", ft_strlen("\\Quit: 3\n"));
		g_all.exit_status = WTERMSIG(p->last_state) + 128;
	}
	g_all.pids_sig = 0;
}

void complex_cmd(t_command *cmd)
{
	t_command *cmdd;
	t_pipe p;
	int i;

	cmdd = cmd;
	p.inp = dup(0);
	p.outp = dup(1);
	i = 0;
	while (cmdd)
	{
		if (!i++ && !cmdd->next)
			single_cmd(cmdd, &p);
		else
		{
			if (cmdd->next)
				multiple_cmds(cmdd, &p);
			else
				last_cmd(cmdd, &p);
		}
		cmdd = cmdd->next;
	}
	waiting_sigs(&p);
}

void execute(t_command *cmd)
{
	if (!cmd->next && is_builtin(cmd->cmd))
		simple_cmd(cmd);
	else
		complex_cmd(cmd);
}