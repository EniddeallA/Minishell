/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:31:22 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/25 03:33:55 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_token **token)
{
	if (!token)
		return (1);
	return (0);
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