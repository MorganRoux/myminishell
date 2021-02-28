/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:49:03 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/09 09:52:00 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** find_bin()
** Search the command in all the paths from the PATH env variable.
** If not found, return the command
** If found, return the whole path of the command
*/

int		err_msg(char *com, int err)
{
	int		ret;

	ret = 0;
	if (err == 1)
	{
		ft_putstr_fd("minishell: fork error\n", STDERR_FILENO);
		ret = 127;
	}
	else if (err == 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(com, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ret = 127;
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(com, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		ret = 126;
	}
	return (ret);
}

int		has_path(char *bin)
{
	while (*bin != 0)
	{
		if (*bin == '/')
			return (1);
		bin++;
	}
	return (0);
}

void	exec_child(t_command *cmd, char *envp[], char *bin, char **params)
{
	if (is_redirection_in(cmd) || is_pipe_in(cmd))
		dup2(cmd->flux_in[0], STDIN_FILENO);
	if (is_redirection_out(cmd) || is_pipe_out(cmd))
		dup2(cmd->flux_out[1], STDOUT_FILENO);
	close(cmd->flux_in[0]);
	close(cmd->flux_in[1]);
	close(cmd->flux_out[0]);
	close(cmd->flux_out[1]);
	if (execve(bin, params, envp) == -1)
		exit(cmd->ret = err_msg(params[0], errno));
}

int		exec_parent(pid_t pid, char *bin, t_command *cmd)
{
	close(cmd->flux_in[0]);
	close(cmd->flux_in[1]);
	close(cmd->flux_out[1]);
	waitpid(pid, &(cmd->status), 0);
	free(bin);
	if (WEXITSTATUS(cmd->status))
		cmd->status = WEXITSTATUS(cmd->status);
	return (cmd->status);
}

/*
** I moved pid to the structure to manage errs
*/

int		exec_command(t_command *cmd, t_command *global_command)
{
	char	**params;
	char	*bin;

	if (cmd->exec == NULL)
		return (1);
	if ((bin = find_bin(cmd->exec, global_command)) == NULL)
		return (-1);
	params = extract_command_and_args(cmd);
	apply_redirections_in(cmd);
	apply_pipe_in(cmd);
	if ((global_command->pid = fork()) < 0)
		return (-1);
	else if (global_command->pid == 0)
		exec_child(cmd, global_command->env_arr, bin, params);
	global_command->ret = exec_parent(global_command->pid, bin, cmd);
	apply_redirections_out(cmd);
	free_strs(params);
	return (1);
}
