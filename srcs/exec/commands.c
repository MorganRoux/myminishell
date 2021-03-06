/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:38:37 by mroux             #+#    #+#             */
/*   Updated: 2021/03/04 21:29:38 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(g_globstruct.ret = err_msg(params[0], errno));
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

int		exec_command(t_command *cmd)
{
	char	**params;
	char	*bin;

	if (cmd->exec == NULL)
		return (1);
	if ((bin = find_bin(cmd)) == NULL)
		return (-1);
	params = extract_command_and_args(cmd);
	apply_redirections_in(cmd);
	apply_pipe_in(cmd);
	if ((g_globstruct.pid = fork()) < 0)
		return (-1);
	else if (g_globstruct.pid == 0)
		exec_child(cmd, g_globstruct.env_arr, bin, params);
	g_globstruct.ret = exec_parent(g_globstruct.pid, bin, cmd);
	g_globstruct.pid = 0;
	apply_redirections_out(cmd);
	free_strs(params);
	return (1);
}
