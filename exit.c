/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 03:01:47 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/03/03 00:14:49 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == ' '))
			i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		if ((result * signe) > 2147483647 || (result * signe) < -2147483648)
			return ((result * signe) % 128);
		i++;
	}
	return ((int)(result * signe));
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (1);
	return (0);
}

void	ft_exit(char **args)
{
	g_all.exit_status = 1;
	if (args[1])
	{
		if (args[2])
			printf("minishell: exit: too many arguments\n");
		else if (!check_str(args[1]))
		{
			printf("exit\n");
			exit(ft_atoi(args[1]));
		}
		else
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				args[1]);
			exit (-1);
		}
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
