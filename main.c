/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/16 16:17:11 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envv)
{
	char *line;
	t_command *cmd;
	t_env *env;

	while ((line = readline("Minishell> ")))
	{
		env = parse_envv(envv);
		cmd = parse_commands(line, env);
	}
	return (0);
}

