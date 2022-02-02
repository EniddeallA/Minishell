/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:08:52 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/02 01:46:52 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);	
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ss;
	char	*sub;
	int		i;

	if (s && start > ft_strlen(s))
		len = 0;
	ss = (char *)s;
	if (ss)
	{
		if ((sub = (char *)malloc(sizeof(char) * (len + 1))) == 0)
			return (0);
		i = 0;
		while (len--)
			sub[i++] = ss[start++];
		sub[i] = '\0';
		return (sub);
	}
	return (0);
}

int check_line()
{
	return (1);
}