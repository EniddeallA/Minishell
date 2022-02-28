/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:22:40 by akhalid           #+#    #+#             */
/*   Updated: 2022/03/01 00:11:24 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	isalpha_num(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}

void	free_tmp(char **tmp)
{
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
}

void	free_rdr(t_redirect *rdr)
{
	t_redirect	*cur;
	t_redirect	*tmp;

	cur = rdr;
	while (cur)
	{
		free(cur->file);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void	free_cmd(void)
{
	t_command	*cur;
	t_command	*tmp;
	int			i;

	if (g_all.cmd == NULL)
		return ;
	cur = g_all.cmd;
	while (cur)
	{
		if (cur->cmd)
			free(cur->cmd);
		i = 0;
		while (cur->args && cur->args[i])
		{
			free(cur->args[i]);
			i++;
		}
		if (cur->args)
			free(cur->args);
		free_rdr(cur->red);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}
