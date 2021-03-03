/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:39:05 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:46:47 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_pipe(t_list_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int		close_pipe(t_list_cmd *cmd)
{
	t_command	*content;
	t_command	*prev;

	content = cmd->content;
	prev = content->prev;
	if (content->pipe != NULL)
		close(content->pipe[1]);
	if (prev != NULL)
		close(prev->pipe[0]);
	return (0);
}

int		apply_pipe_in(t_command *cmd)
{
	t_command	*prev;
	char		buf;

	prev = cmd->prev;
	if (!is_pipe_in(cmd))
		return (0);
	while (read(prev->pipe[0], &buf, 1) > 0)
		write(cmd->flux_in[1], &buf, 1);
	close(prev->pipe[0]);
	return (0);
}

int		apply_pipe_out(t_command *cmd)
{
	if (!is_pipe_out(cmd))
		return (0);
	close(cmd->pipe[0]);
	dup2(cmd->pipe[1], STDOUT_FILENO);
	close(cmd->pipe[1]);
	return (0);
}

int		apply_pipes(t_command *cmd)
{
	if (is_pipe_out(cmd))
		apply_pipe_out(cmd);
	if (is_pipe_in(cmd))
		apply_pipe_in(cmd);
	return (1);
}
