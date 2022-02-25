/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 05:28:26 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/25 03:02:28 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd1(void)
{
	char	*oldpwd;
	char	*tmp;

	if (!key_exist("HOME"))
		printf("minishell: cd: HOME not set\n");
	else
	{
		oldpwd = getcwd(NULL, 0);
		replace_value("OLDPWD", oldpwd);
		tmp = get_value("HOME");
		chdir(tmp);
		replace_value("PWD", tmp);
	}
}

void	ft_cd(char **args)
{
	char	*oldpwd;
	char	*tmp;

	if (n_args(args) == 1)
		ft_cd1();
	else
	{
		oldpwd = getcwd(NULL, 0);
		if (chdir(args[1]) == 0)
		{
			replace_value("OLDPWD", oldpwd);
			tmp = getcwd(NULL, 0);
			replace_value("PWD", tmp);
		}
		else
		{
			free(oldpwd);
			printf("minishell: cd: %s: No such file or directory\n", args[1]);
		}
	}
}
