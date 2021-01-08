/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:23:44 by alkanaev          #+#    #+#             */
/*   Updated: 2020/12/28 17:22:16 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     exec_built_ins(t_command *global_cmd, char **cmd)
{
    if (!ft_strcmp(cmd[0], "echo"))
		com_echo(global_cmd, cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
	 	com_cd(global_cmd, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
	 	com_env(global_cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
	 	com_pwd(global_cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
	 	com_exit(global_cmd, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
	 	com_unset(global_cmd, cmd);
	else if (!ft_strcmp(cmd[0], "export"))
	 	com_export(global_cmd, cmd);
	else
		return (0);
	return (1);
}

void    exec(t_command *global_cmd, t_list_cmd  *cmds)
{
    char        **cmd;
    while (cmds != NULL)
    {
        cmd = extract_command_and_args(cmds->content);
        if (cmd[0] == 0)
		    global_cmd->ret = 127;
        if(open_redirections(cmds) == -1)
            return;
        // if(open_pipe(cmds) == -1)
        //     return;
	    if (exec_built_ins(global_cmd, cmd) != 1)
            exec_command(cmds->content, global_cmd->env_arr);
        //close_pipe(cmds);
        // close_redirections(cmds);
        cmds = cmds->next;
    }
}

