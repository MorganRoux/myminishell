/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:39:17 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:46:41 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		load_files(t_list_str *files, int flags, int *fd, int *i)
{
	char		*path;

	while (files != NULL)
	{
		path = files->content;
		fd[*i] = open(path, flags, S_IRWXU);
		if (fd[*i] < 0)
		{
			ft_printf("erreur %d avec %s\n", fd[*i], path);
			return (-1);
		}
		files = files->next;
		(*i)++;
	}
	return (0);
}

int		*open_fds_out(t_command *content)
{
	int			i;
	int			*fd;
	t_list_str	*files_out;
	t_list_str	*files_append;

	files_out = content->files_out;
	files_append = content->files_append;
	i = 0;
	if (!(fd = malloc(sizeof(int) *
		(ft_lstsize(files_out) + ft_lstsize(files_append)))))
		return (NULL);
	if ((load_files(files_out, O_WRONLY | O_CREAT | O_TRUNC, fd, &i) != -1) &&
		(load_files(files_append, O_WRONLY | O_CREAT | O_APPEND, fd, &i) != -1))
		return (fd);
	free(fd);
	return (NULL);
}

int		open_redirections(t_list_cmd *cmd)
{
	t_command	*content;

	content = cmd->content;
	if ((content->fd_in = open_fds_in(content)) == NULL ||
		(content->fd_out = open_fds_out(content)) == NULL)
		return (-1);
	return (0);
}

int		close_fds(int *fds, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (close(fds[i++]) == -1)
			return (-1);
	}
	return (0);
}

int		close_redirections(t_list_cmd *cmd)
{
	t_command	*content;

	content = cmd->content;
	close_fds(content->fd_in, ft_lstsize(content->files_in));
	close_fds(content->fd_out, ft_lstsize(content->files_out));
	return (0);
}
