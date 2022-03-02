/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:40:13 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/03/02 02:37:37 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buff;
	char	*temp;

	buff = getcwd(NULL, 0);
	g_all.exit_status = 1;
	if (buff)
	{
		printf("%s\n", buff);
		free(buff);
		g_all.exit_status = 0;
	}
	else
	{
		temp = get_value("PWD");
		if (temp)
		{
			replace_value("PWD", temp);
			printf("%s\n", temp);
			g_all.exit_status = 0;
		}	
		else
			printf("minishell: cd: .: No such file or directory\n");
	}
}
