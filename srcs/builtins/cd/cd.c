/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:19:48 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:20:37 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_and_extract_cd_argument(t_command *cmd)
{
	if (cmd->args == NULL)
		return (ft_strdup("~"));
	if (ft_lstsize(cmd->args) != 1)
		return (NULL);
	return (ft_strdup(ft_lstof(cmd->args, 0)->content));
}

char	*replace_tilde(char *new_dir)
{
	char	*ret;
	char	*home;

	home = get_var(g_globstruct.env_arr, "HOME");
	ret = ft_strjoin(home, ++new_dir);
	free(--new_dir);
	free(home);
	return (ret);
}

int		cd(t_command *cmd)
{
	char	*new_dir;

	if ((new_dir = check_and_extract_cd_argument(cmd)) == NULL)
	{
		ft_putstr_fd("error", 2);
		return (2);
	}
	if (new_dir[0] == '~')
		new_dir = replace_tilde(new_dir);
	if (chdir(new_dir) == -1)
	{
		free(new_dir);
		ft_putstr_fd("error\n", 2);
		return (1);
	}
	free(new_dir);
	return (0);
}
