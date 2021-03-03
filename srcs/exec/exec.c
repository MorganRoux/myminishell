/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:38:05 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:47:07 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		do_built_ins(t_command *cmd)
{
	if (!ft_strcmp(cmd->exec, "echo"))
		return (echo(cmd));
	if (!ft_strcmp(cmd->exec, "env"))
		return (env(cmd));
	if (!ft_strcmp(cmd->exec, "pwd"))
		return (pwd(cmd));
	if (!ft_strcmp(cmd->exec, "cd"))
		return (cd(cmd));
	if (!ft_strcmp(cmd->exec, "exit"))
		do_exit(cmd);
	if (!ft_strcmp(cmd->exec, "unset"))
		return (unset(cmd));
	if (!ft_strcmp(cmd->exec, "export"))
		return (export(cmd));
	return (0);
}

int		exec_built_ins(t_command *cur_cmd)
{
	int		saved_stdin;
	int		saved_stdout;

	apply_redirections_in(cur_cmd);
	apply_pipe_in(cur_cmd);
	close(cur_cmd->flux_in[1]);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (is_redirection_in(cur_cmd) || is_pipe_in(cur_cmd))
		dup2(cur_cmd->flux_in[0], STDIN_FILENO);
	if (is_redirection_out(cur_cmd) || is_pipe_out(cur_cmd))
		dup2(cur_cmd->flux_out[1], STDOUT_FILENO);
	g_globstruct.ret = do_built_ins(cur_cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(cur_cmd->flux_out[1]);
	close(cur_cmd->flux_in[0]);
	apply_redirections_out(cur_cmd);
	return (1);
}

int		is_built_in(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "exit") ||
		!ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

int		exec(t_list_cmd *cmds)
{
	t_command	*cur_cmd;

	while (cmds != NULL)
	{
		cur_cmd = cmds->content;
		if (cur_cmd->exec == 0)
			g_globstruct.ret = 127;
		if (open_redirections(cmds) == -1)
		{
			g_globstruct.ret = 1;
			return (-1);
		}
		if (is_built_in(cur_cmd->exec))
			exec_built_ins(cur_cmd);
		else
			exec_command(cmds->content);
		cmds = cmds->next;
	}
	return (0);
}

void	exec_loop(char *line)
{
	char		**command_list;
	int			i;
	t_list_cmd	*cmds;
	t_list_cmd	*new_cmd;

	i = 0;
	cmds = NULL;
	if (check_errors(line))
		return ;
	command_list = split_commands(line);
	while (command_list[i] != NULL)
	{
		command_list[i] = solve_dollards(command_list[i]);
		new_cmd = parse(command_list[i]);
		if (cmds != NULL)
			link_commands(ft_lstlast(cmds), new_cmd);
		ft_lstadd_back(&cmds, new_cmd);
		if (exec(ft_lstlast(cmds)) == -1)
			break ;
		i++;
	}
	free_strs(command_list);
	free_cmds(cmds);
}
