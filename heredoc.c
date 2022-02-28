/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:32:15 by akhalid           #+#    #+#             */
/*   Updated: 2022/03/01 00:32:01 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredocs(t_command *cmd)
{
	t_command	*curr;
	t_redirect	*red;
	char		*file;

	curr = cmd;
	while (curr)
	{
		red = curr->red;
		while (red)
		{
			if (red->type == HRDOC)
			{
				file = ft_strjoin(ft_strdup("/tmp/file"), ft_itoa(red->index));
				close(red->fd);
				unlink(file);
				free(file);
			}
			red = red->next;
		}
		curr = curr->next;
	}
}

int	open_heredoc(t_redirect *red)
{
	int		fd;
	char	*doc;
	char	*str;

	doc = ft_strjoin(ft_strdup("/tmp/file"), ft_itoa(red->index));
	fd = open(doc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (!ft_strcmp(red->file, str))
		{
			free(str);
			break ;
		}
		str = ft_strjoin(str, ft_strdup("\n"));
		write(fd, str, ft_strlen(str));
		free(str);
	}
	close(fd);
	fd = open(doc, O_RDONLY, 0644);
	free(doc);
	return (fd);
}

void	open_heredocs(t_command *cmd)
{
	t_command	*curr;
	t_redirect	*red;
	int			i;

	curr = cmd;
	i = 0;
	while (curr)
	{
		red = curr->red;
		while (red)
		{
			if (red->type == HRDOC)
			{
				red->index = i++;
				red->fd = open_heredoc(red);
			}
			red = red->next;
		}
		curr = curr->next;
	}
}
