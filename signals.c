/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:45:58 by akhalid           #+#    #+#             */
/*   Updated: 2022/03/03 02:05:49 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting_sigs(t_pipe *p)
{
	g_all.pids_sig = 42;
	while (waitpid(-1, &p->state, 0) > 0)
		;
	if (WIFEXITED(p->state))
		g_all.exit_status = WEXITSTATUS(p->state);
	else if (WIFSIGNALED(p->state))
	{
		if (WTERMSIG(p->state) == SIGQUIT)
			write(2, "\\Quit: 3\n", ft_strlen("\\Quit: 3\n"));
		g_all.exit_status = WTERMSIG(p->state) + 128;
	}
	if (g_all.exit_status == 141)
		g_all.exit_status = 0;
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
