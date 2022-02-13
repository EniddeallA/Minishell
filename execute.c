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

/* 
	execute a simple built-in command 
*/

void simple_cmd(t_command *cmd)
{

}

void redirect(t_command *cmd)
{

}

void execute_cmd(t_command *cmd)
{

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
	close(p->inps);
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
		{
			dup2(p->inp, 0);
			close(p->inp);
		}
		redirect(cmd);
		execute_cmd(cmd);
	}
	if (p->pipe[1] != 1)
		close(p->pipe[1]);
	if (p->inp)
		close(p->inp);
}

/* 
	execute a complex command 
*/

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
		if (!i++ && !current->next)
			single_cmd(cmdd, &p);
		else
		{
			if (current->next)
				multiple_cmds(cmdd, &p);
			else
				last_cmd(cmdd, &p);
		}
		cmdd = cmdd->next;
	}
}

void execute(t_command *cmd)
{
	if (!cmd->next && is_builtin(cmd->cmd))
		simple_cmd(cmd);
	else
		complex_cmd(cmd);
}	