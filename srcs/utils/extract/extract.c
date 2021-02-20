/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 09:36:01 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/30 09:38:57 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     get_strs_len(char **strs)
{
    int i;

    i = 0;
    if (strs == 0)
        return 0;
    while (strs[i] != NULL)
        i++;
    return (i);
}

char	**list2char(t_list_str *lst)
{
	char		**strs;
	int			count;

	count = ft_lstsize(lst) + 1;
	strs = malloc((count + 1) * sizeof(char *));
	count = 0;
	while (lst != 0)
	{
		strs[count++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	strs[count] = 0;
	return (strs);
}

char	**extract_command(char **strs, t_command *cmd)
{
	*strs = ft_strdup(cmd->exec);
	strs++;
	return (strs);
}

char	**extract_args(char **strs, t_command *cmd)
{
	t_list_str	*args;

	args = cmd->args;
	while (args != 0)
	{
		*strs++ = ft_strdup(args->content);
		args = args->next;
	}
	return (strs);
}

char	**extract_command_and_args(t_command *cmd)
{
	char	**strs;
	int		count;

	count = ft_lstsize(cmd->args) + 1;
	strs = malloc((count + 1) * sizeof(char *));
	strs = extract_command(strs, cmd);
	strs = extract_args(strs, cmd);
	*strs = 0;
	strs = strs - count;
	return (strs);
}
