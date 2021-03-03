/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:39:39 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:39:49 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_bin_with_env(char *bin)
{
	char	*full_bin;
	char	**paths;
	int		i;

	i = 0;
	if ((paths = get_paths(g_globstruct.env_arr)) == NULL)
		return (ft_strdup(bin));
	full_bin = ft_strjoin(paths[0], bin);
	while (open(full_bin, O_RDONLY) == -1)
	{
		free(full_bin);
		if (paths[++i] == 0)
		{
			free_strs(paths);
			g_globstruct.ret = err_msg(bin, 2);
			return (NULL);
		}
		full_bin = ft_strjoin(paths[i], bin);
	}
	free_strs(paths);
	return (full_bin);
}

char	*find_bin(char *bin)
{
	if (has_path(bin))
		return (ft_strdup(bin));
	else
		return (find_bin_with_env(bin));
}

void	link_commands(t_list_cmd *l_cmd, t_list_cmd *new_cmd)
{
	t_command	*last_content;
	t_command	*new_content;

	new_content = new_cmd->content;
	last_content = l_cmd->content;
	if (last_content->pipe != NULL)
		new_content->prev = l_cmd->content;
}

int		*open_fds_in(t_command *content)
{
	char		*path;
	int			i;
	int			*fd;
	t_list_str	*files;

	files = content->files_in;
	i = 0;
	if (!(fd = malloc(sizeof(int) * ft_lstsize(files))))
		return (NULL);
	while (files != NULL)
	{
		path = files->content;
		fd[i] = open(path, O_RDONLY, S_IRWXU);
		if (fd[i] < 0)
		{
			ft_printf("erreur %d avec %s\n", fd[i], path);
			return (NULL);
		}
		files = files->next;
		i++;
	}
	return (fd);
}
