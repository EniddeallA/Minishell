/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:37:00 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/08 01:53:17 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command()
{
	t_command *cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->n_arg = 0;
	cmd->red = NULL;
	cmd->next = NULL;
	return (cmd);
}

void 	token_to_cmd(t_token **tokens, t_command *cmd, int i)
{
	if (tokens[i]->type == WRD)
	{
		if (!cmd->args)
			cmd->cmd = ft_strdup(tokens[i]->val);
		cmd->args = realloc_args(cmd->args, tokens[i]->val);
	}
	else if (tokens[i]->type == IN || tokens[i]->type == OUT ||
		tokens[i]->type == APND || tokens[i]->type == HRDOC)
		if (!cmd->red)
			cmd->red = init_redirection(tokens[i + 1]->val, tokens[i]->type);
		else
			
}