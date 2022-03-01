/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:40:13 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/03/01 16:46:51 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buff;
	char	*temp;

	buff = getcwd(NULL, 0);
	if (buff)
	{
		printf("%s\n", buff);
		free(buff);
	}
	else
	{
		temp = get_value("PWD");
		if (temp)
		{
			replace_value("PWD", temp);
			printf("%s\n", temp);
		}	
		else
			printf("minishell: cd: .: No such file or directory\n");
	}
}
