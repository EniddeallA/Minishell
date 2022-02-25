/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 22:32:10 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/25 03:33:23 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cntl_c(int sig)
{
	int	i;

	i = sig;
	if (g_all.pids_sig == 0)
	{
		g_all.exit_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		i = 0;
	}
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	execute_builtins(t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd->args);
}

void	wait_sigs(t_pipe *p)
{
	g_all.pids_sig = 1;
	waitpid(p->last_pid, &(p->state), 0);
	if (WIFEXITED(p->state))
		g_all.exit_status = WEXITSTATUS(p->state);
	g_all.pids_sig = 0;
}
