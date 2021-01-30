/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_meta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:19:31 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/30 10:26:41 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	g_globstruct;

int		is_meta_char(char c)
{
	char	METACHARACTER[] = " \t\n|&;()<>";
	int		i;

	i = 0;
	while (METACHARACTER[i] != 0)
	{
		if (METACHARACTER[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		is_meta_str(char *c)
{
	char	METACHARACTER[] = " \t\n|&;()<>";
	int		i;

	i = 0;
	while (METACHARACTER[i] != 0)
	{
		if (METACHARACTER[i] == c[0])
			return (1);
		i++;
	}
	return (0);
}

int		is_space_str(char *c)
{
	char	METACHARACTER[] = " \t";
	int		i;

	i = 0;
	while (METACHARACTER[i] != 0)
	{
		if (METACHARACTER[i] == c[0])
			return (1);
		i++;
	}
	return (0);
}
