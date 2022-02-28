/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 22:32:10 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/28 22:48:30 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
