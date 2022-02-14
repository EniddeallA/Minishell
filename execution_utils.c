/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 22:32:10 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/13 22:32:29 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
	!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
	!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
	!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
