/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:02 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/31 04:17:51 by eniddealla       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_key(char *str)
{
	int i;
	char *key;
	int length;

	length = 0;
	while (str[length] && str[length] != '=')
		length++;
	i = 0;
	key = (char *)malloc(sizeof(char) * (length + 1));
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;	
	}
	key[i] = '\0';
	return (key);
}

char *get_value(char *str)
{
	int i;
	char *value;
	int index;
	int length;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			index = i + 1;
		i++;
	}
	length = i - index;
	value = (char *)malloc(sizeof(char) * (length + 1));
	i = 0;
	while (str[index])
		value[i++] = str[index++];
	value[i] = '\0';
	return (value);
}

t_env *create_node(char *envv)
{
	t_env *node;
	
	node = (t_env *)malloc(sizeof(t_env));
	node->key = get_key(envv);
	node->value = get_value(envv);
	node->next = NULL;
	return (node);
}

void collect_env(char **envv)
{
	int i;
	t_env *head;
	t_env *last;
	t_env *new;

	head = NULL;
	i = 0;
	while (envv[i])
	{
		last = head;
		new = create_node(envv[i]);
		if (!head)
			head = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
		i++;
	}
	g_all.env = head;
}

void parse_line(char *line)
{
	
}

int main(int argc, char **argv, char **envv)
{
	char *line;
	
	(void)argc;
	(void)argv;
	collect_env(envv);
	while ((line = readline("Minishell> ")))
	{
		add_history(line);
		parse_line(line);
	}
	return (0);
}
