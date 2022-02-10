/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:37:00 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/08 01:56:30 by akhalid          ###   ########.fr       */
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

void	free_args(char **args)
{
	int i;
	
	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

char **realloc_args(char **args, char *val)
{
	int i;
	char **new_args;
	
	i = 0;
	if (val[0] == ' ' && val[1] == '\0')
		return (args);
	if (args)
		while (args[i])
			i++;
	new_args = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	if (args)
		while (args[i])
		{
			new_args[i] = ft_strdup(args[i]);
			i++;
		}
	new_args[i++] = ft_strdup(val);
	new_args[i] = NULL;
	i = 0;
	free_args(args);
	return (new_args);
}

void 	token_to_cmd(t_token **tokens, t_command *cmd, int i)
{
	if (tokens[i]->type == WRD)
	{
		if (!cmd->args)
			cmd->cmd = ft_strdup(tokens[i]->val);
		cmd->args = realloc_args(cmd->args, tokens[i]->val);
	}
	else if (tokens[i]->type == INP || tokens[i]->type == OUT ||
		tokens[i]->type == APND || tokens[i]->type == HRDOC)
	{
		if (!cmd->red)
			cmd->red = init_redirection(tokens[i + 1]->val, tokens[i]->type);
		else
			create_redirection(cmd->red, tokens[i + 1]->val, tokens[i]->type);
	}
}
