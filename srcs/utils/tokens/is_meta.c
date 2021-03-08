/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_meta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:09 by mroux             #+#    #+#             */
/*   Updated: 2021/03/08 20:34:10 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_meta_char(char c)
{
	char	*metacharacter;
	int		i;

	metacharacter = ft_strdup(" \t\n|&;()<>");
	i = 0;
	while (metacharacter[i] != 0)
	{
		if (metacharacter
[i] == c)
		{
			free(metacharacter);
			return (1);
		}
		i++;
	}
	free(metacharacter);
	return (0);
}

int		is_meta_str(char *c)
{
	char	*metacharacter;
	int		i;

	i = 0;
	metacharacter = ft_strdup(" \t\n|&;()<>");
	while (metacharacter[i] != 0)
	{
		if (metacharacter
[i] == c[0])
		{
			free(metacharacter);
			return (1);
		}
		i++;
	}
	free(metacharacter);
	return (0);
}

int		is_space_str(char *c)
{
	char	*metacharacter;
	int		i;

	i = 0;
	metacharacter = ft_strdup(" \t");
	while (metacharacter[i] != 0)
	{
		if (metacharacter
[i] == c[0])
		{
			free(metacharacter);
			return (1);
		}
		i++;
	}
	free(metacharacter);
	return (0);
}
