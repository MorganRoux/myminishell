/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:51:50 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/09 13:09:39 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** find_bin_with_env and find_bin - from commands.c
** find_bin()
** Search the command in all the paths from the PATH env variable.
** If not found, return the command
** If found, return the whole path of the command
*/

char	*find_bin_with_env(char *bin, t_command *gc)
{
	char	*full_bin;
	char	**paths;
	int		i;

	i = 0;
	paths = get_paths(gc->env_arr);
	full_bin = ft_strjoin(paths[0], bin);
	while (open(full_bin, O_RDONLY) == -1)
	{
		free(full_bin);
		if (paths[++i] == 0)
		{
			free_strs(paths);
			gc->ret = err_msg(bin, 2);
			return (NULL);
		}
		full_bin = ft_strjoin(paths[i], bin);
	}
	free_strs(paths);
	return (full_bin);
}

char	*find_bin(char *bin, t_command *global_command)
{
	if (has_path(bin))
		return (ft_strdup(bin));
	else
		return (find_bin_with_env(bin, global_command));
}

/*
** void	link_commands - from exec.c
*/

void	link_commands(t_list_cmd *l_cmd, t_list_cmd *new_cmd)
{
	t_command	*last_content;
	t_command	*new_content;

	new_content = new_cmd->content;
	last_content = l_cmd->content;
	if (last_content->pipe != NULL)
		new_content->prev = l_cmd->content;
}

/*
** open_fds_in - from redirections.c
*/

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
