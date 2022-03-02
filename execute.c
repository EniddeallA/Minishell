/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:03:54 by akhalid           #+#    #+#             */
/*   Updated: 2022/03/02 21:14:53 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_cmd(t_command *cmd, t_pipe *p)
{
	p->pid = fork();
	p->last_pid = p->pid;
	if (!p->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		redirect(cmd);
		if (g_all.exit_status != 1 || !g_all.ret)
			execute_cmd(cmd);
	}
	close(p->inp);
	close(p->outp);
}

void	multiple_cmds(t_command *cmd, t_pipe *p)
{
	pipe(p->pipe);
	close(p->outp);
	p->outp = p->pipe[1];
	p->pid = fork();
	if (!p->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(p->outp, 1);
		close(p->pipe[1]);
		dup2(p->inp, 0);
		close(p->pipe[0]);
		redirect(cmd);
		if (g_all.exit_status != 1 || !g_all.ret)
			execute_cmd(cmd);
	}
	if (p->inp > 2)
		close(p->inp);
	p->inp = p->pipe[0];
	close(p->outp);
}

void	last_cmd(t_command *cmd, t_pipe *p)
{
	p->pid = fork();
	p->last_pid = p->pid;
	if (!p->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		if (p->inp)
			dup2(p->inp, 0);
		if (p->inp)
			close(p->inp);
		redirect(cmd);
		if (g_all.exit_status != 1 || !g_all.ret)
			execute_cmd(cmd);
	}
	if (p->pipe[1] != 1)
		close(p->pipe[1]);
	if (p->inp)
		close(p->inp);
}

void	complex_cmd(t_command *cmd)
{
	t_command	*cmdd;
	t_pipe		p;
	int			i;

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

void	simple_cmd(t_command *cmd)
{
	int	inp;
	int	outp;

	inp = dup(0);
	outp = dup(1);
	redirect(cmd);
	if (g_all.exit_status != 1 || !g_all.ret)
		execute_builtins(cmd);
	dup2(inp, 0);
	dup2(outp, 1);
	close(inp);
	close(outp);
}
