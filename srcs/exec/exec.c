/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:23:44 by alkanaev          #+#    #+#             */
/*   Updated: 2020/12/19 14:35:15 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     exec_command(t_command *cmd, char *envp[])
{

    (void)cmd;
    (void)envp;
    print_cmd(cmd);
    return (1);
}

int     exec_built_ins(t_command *mimi, char **cmd)
{
    if (!ft_strcmp(cmd[0], "echo"))
		com_echo(mimi, cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
	 	com_cd(mimi, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
	 	com_env(mimi);
	else if (!ft_strcmp(cmd[0], "pwd"))
	 	com_pwd(mimi);
	else if (!ft_strcmp(cmd[0], "exit"))
	 	com_exit(mimi, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
	 	com_unset(mimi, cmd);
	else if (!ft_strcmp(cmd[0], "export"))
	 	com_export(mimi, cmd);
	else
		return (0);
	return (1);
}

void     exec1(t_list_cmd  *cmds)
{
    print_cmds(cmds);
}

void    exec2(t_command *mimi, char **cmd, t_list_cmd  *cmds, char *envp[])
{
	if (cmd[0] == 0)
		mimi->ret = 127;
	if (exec_built_ins(mimi, cmd))
        return;
    exec_command(cmds->content, envp);
}

