/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:42:18 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:42:48 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicate_strs(char **strs)
{
	char	**dup;
	int		i;

	i = 0;
	if (strs == NULL)
		return (NULL);
	if (!(dup = malloc(sizeof(char *) * (get_strs_len(strs) + 1))))
		return (NULL);
	while (strs[i] != NULL)
	{
		dup[i] = ft_strdup(strs[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	ft_sort_string_tab(char **tab)
{
	int		end;
	int		i;
	char	*tmp;

	end = 0;
	while (!end)
	{
		end = 1;
		i = 0;
		while (tab[i + 1] != 0)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				end = 0;
			}
			i++;
		}
	}
}
