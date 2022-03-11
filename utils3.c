/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:31:22 by akhalid           #+#    #+#             */
/*   Updated: 2022/03/03 02:16:39 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_token **tokens)
{
	t_type	prev;
	t_type	curr;
	int		i;

	i = 0;
	prev = -1;
	curr = 0;
	g_all.exit_status = 258;
	while (tokens[i])
	{
		curr = tokens[i]->type;
		if (prev != WRD && i != 0 && curr != WRD
			&& prev != PIPE && curr != PIPE)
			return (0);
		if (i == 0 && curr == PIPE)
			return (0);
		prev = curr;
		i++;
	}
	if (curr != WRD)
		return (0);
	g_all.exit_status = 0;
	return (1);
}

int	check_line(void)
{
	if (g_all.line == NULL)
	{
		write(1, "exit\n", 6);
		return (0);
	}
	return (1);
}

char	*concatenate(char *str, char *cmd, char *path)
{
	str = ft_strdup(path);
	str = ft_strjoin(str, ft_strdup("/"));
	str = ft_strjoin(str, ft_strdup(cmd));
	return (str);
}

void	check_exec(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) && S_ISDIR(buf.st_mode))
	{
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", ft_strlen(": is a directory\n"));
		exit(126);
	}
}

t_token	*free_val(char	*val)
{
	free(val);
	return (0);
}
