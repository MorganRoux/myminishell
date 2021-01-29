/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir_sup2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:14:16 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/29 14:45:19 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** for redirections 2nd
*/

int		apply_redirections_in(t_command *cmd)
{
	char	buf;
	int		i;

	i = 0;
	if (is_redirection_in(cmd))
	{
		while (i < number_of_redirection_in(cmd))
		{
			while (read(cmd->fd_in[i], &buf, 1) > 0)
				write(cmd->flux_in[1], &buf, 1);
			close(cmd->fd_in[i]);
			i++;
		}
		close_fds(cmd->fd_in, number_of_redirection_in(cmd));
		close(cmd->flux_in[1]);
	}
	return (1);
}

int		apply_redirections_out(t_command *cmd)
{
	char	buf;
	int		i;

	if (is_redirection_out(cmd) || is_pipe_out(cmd))
	{
		while (read(cmd->flux_out[0], &buf, 1) > 0)
		{
			i = 0;
			while (i < number_of_redirection_out(cmd))
				write(cmd->fd_out[i++], &buf, 1);
			if (is_pipe_out(cmd))
				write(cmd->pipe[1], &buf, 1);
		}
		close_fds(cmd->fd_out, number_of_redirection_out(cmd));
		close(cmd->flux_out[0]);
		if (is_pipe_out(cmd))
			close(cmd->pipe[1]);
	}
	return (1);
}

int		is_redirection_out(t_command *cmd)
{
	return (number_of_redirection_out(cmd) == 0 ? 0 : 1);
}

int		apply_redirections(t_command *cmd)
{
	apply_redirections_in(cmd);
	apply_redirections_out(cmd);
	return (1);
}
