/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_sup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:38:46 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:46:58 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** for pipes
*/

int		is_pipe_out(t_command *cmd)
{
	return (cmd->pipe == NULL ? 0 : 1);
}

int		is_pipe_in(t_command *cmd)
{
	return (cmd->prev == NULL ? 0 : 1);
}

/*
** for redirections 1st
*/

int		number_of_redirection_out(t_command *cmd)
{
	return (ft_lstsize(cmd->files_out) + ft_lstsize(cmd->files_append));
}

int		number_of_redirection_in(t_command *cmd)
{
	return (ft_lstsize(cmd->files_in));
}

int		is_redirection_in(t_command *cmd)
{
	return (number_of_redirection_in(cmd) == 0 ? 0 : 1);
}
