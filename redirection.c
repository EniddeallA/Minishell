/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 04:44:31 by akhalid           #+#    #+#             */
/*   Updated: 2022/03/02 02:20:47 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_file(t_redirect *red)
{
	int	fd;

	fd = -1;
	if (red->type == INP)
		fd = open(red->file, O_RDONLY, 0644);
	else if (red->type == OUT)
		fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->type == APND)
		fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		printf("%s\n", strerror(errno));
	return (fd);
}

void	redirect_file(t_redirect *red)
{
	int			tmp_fd;
	t_redirect	*curr;

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

void	redirect(t_command *cmd)
{
	t_redirect	*red;

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
