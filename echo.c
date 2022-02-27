/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:41:56 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/27 21:35:41 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"

int	is_option(char *args)
{
	int	i;

	i = 0;
	if (args && args[0] == '-' && args[1])
	{
		i++;
		while (args[i])
		{
			if (args[i] != 'n')
				return (0);
			i++;
		}
	}
	return (i);
}

int	get_index(char **args)
{
	int	i;

	i = 1;
	if (is_option(args[1]))
	{
		while (args[i])
		{
			if (!is_option(args[i]))
				return (i);
			i++;
		}
	}
	return (i);
}

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	ft_echo(char **args)
{
	int	i;
	int	option;

	option = is_option(args[1]);
	i = get_index(args);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_args(args) == 1 || option == 0)
		write(1, "\n", 1);
}
