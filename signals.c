/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:45:58 by akhalid           #+#    #+#             */
/*   Updated: 2022/03/01 00:22:03 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting_sigs(t_pipe *p)
{
	g_all.pids_sig = 42;
	waitpid(p->last_pid, &p->laststat, 0);
	while (waitpid(-1, &p->state, 0) > 0)
		;
	if (WIFEXITED(p->laststat))
		g_all.exit_status = WEXITSTATUS(p->laststat);
	else if (WIFSIGNALED(p->laststat))
	{
		if (WTERMSIG(p->laststat) == SIGQUIT)
			write(2, "\\Quit: 3\n", ft_strlen("\\Quit: 3\n"));
		g_all.exit_status = WTERMSIG(p->laststat) + 128;
	}
	g_all.pids_sig = 0;
}

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
