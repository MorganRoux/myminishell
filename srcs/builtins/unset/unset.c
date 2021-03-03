/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:34:16 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:35:36 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset_from_env(char *env[], int index)
{
	char	**new_env;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	if ((len = get_strs_len(env)) == -1)
		return (NULL);
	if (!(new_env = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	while (i < len)
	{
		if (i != index)
		{
			new_env[j] = strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_strs(env);
	return (new_env);
}

int		unset(t_command *cmd)
{
	t_list_str	*args;
	int			index;

	if ((args = cmd->args) == NULL)
		return (0);
	while (args != NULL)
	{
		index = get_var_index(g_globstruct.env_arr, args->content);
		if (index != -1)
			g_globstruct.env_arr = unset_from_env(g_globstruct.env_arr, index);
		args = args->next;
	}
	return (0);
}
