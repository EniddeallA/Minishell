/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:03:54 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/12 17:14:06 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
	!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
	!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
	!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void simple_cmd(t_command *cmd)
{
	/* execute a simple built-in command */
}

void complex_cmd(t_command *cmd)
{
	/* execute a complex command */
}

void execute(t_command *cmd)
{
	if (!cmd->next && is_builtin(cmd->cmd))
		simple_cmd(cmd);
	else
		complex_cmd(cmd);
}