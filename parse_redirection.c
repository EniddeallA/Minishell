/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:58:05 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/08 02:03:07 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*init_redirection(char *val, t_type type)
{
	t_redirect *red;

	red = (t_redirect *)malloc(sizeof(t_redirect));
	red->file = ft_strdup(val);
	red->type = type;
	red->type = NULL;
	return (red);
}

void 	create_redirection(t_redirect *red, char *val, t_type type)
{
	t_redirect *new;
	t_redirect *current;
	
	current = red;
	while (current->next)
		current = current->next;
	new = (t_redirect *)malloc(sizeof(t_redirect));
	new->file = ft_strdup(val);
	new->type = type;
	new->next = NULL;
	current->next = new;
}