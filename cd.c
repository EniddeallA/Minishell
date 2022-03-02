/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 05:28:26 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/03/02 21:35:22 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd1(void)
{
	char	*oldpwd;
	char	*tmp;

	if (!key_exist("HOME"))
	{
		printf("minishell: cd: HOME not set\n");
		g_all.exit_status = 1;
	}
	else
	{
		oldpwd = getcwd(NULL, 0);
		replace_value("OLDPWD", oldpwd);
		free(oldpwd);
		tmp = get_value("HOME");
		chdir(tmp);
		replace_value("PWD", tmp);
		g_all.exit_status = 0;
	}
}

void	free_tmpp(char *tmp, int i)
{
	free(tmp);
	if (i)
		g_all.exit_status = 1;
	else
		g_all.exit_status = 0;
}

void	update_pwds(void)
{
	char	*oldnode;
	char	*currentnode;
	char	*pwd;

	oldnode = get_value("OLDPWD");
	currentnode = get_value("PWD");
	if (oldnode)
		oldnode = ft_strdup(currentnode);
	if (currentnode)
	{
		pwd = (char *)malloc(sizeof(char) * 100);
		getcwd(pwd, 100);
		currentnode = pwd;
	}
}

void	ft_cd(char **args)
{
	g_all.exit_status = 0;
	if (n_args(args) == 1 || !ft_strcmp(args[1], "~"))
		ft_cd1();
	else
	{
		if (chdir(args[1]) == 0)
			update_pwds();
		else
		{
			write(2, args[1], ft_strlen(args[1]));
			perror(": ");
			g_all.exit_status = 1;
		}
	}
}
