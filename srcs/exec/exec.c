/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:23:44 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/18 19:19:12 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_child_built_ins(t_command *global_cmd, char **cmd, t_command *cur_cmd)
{
    if (is_redirection_in(cur_cmd) || is_pipe_in(cur_cmd))
        dup2(cur_cmd->flux_in[0], STDIN_FILENO);
    if (is_redirection_out(cur_cmd) || is_pipe_out(cur_cmd))
        dup2(cur_cmd->flux_out[1], STDOUT_FILENO);
    close(cur_cmd->flux_in[0]);
    close(cur_cmd->flux_in[1]);
    close(cur_cmd->flux_out[0]);
    close(cur_cmd->flux_out[1]);

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
		exit(0);
	exit(1);
}

int     exec_parent_built_ins(pid_t pid, t_command *cmd)
{
    close(cmd->flux_in[0]);
    close(cmd->flux_in[1]);
    //close(cmd->flux_out[0]);
    close(cmd->flux_out[1]);
    waitpid(pid, &(cmd->status), 0);
    return (cmd->status);    
}

int     exec_built_ins(t_command *global_cmd, char **cmd, t_command *cur_cmd)
{
    apply_redirections_in(cur_cmd);
    apply_pipe_in(cur_cmd);
    if ((global_cmd->pid = fork()) < 0) 
        return -1;
    else if (global_cmd->pid == 0)
        exec_child_built_ins(global_cmd, cmd, cur_cmd);  //cmd, global_command->env_arr, bin, params);
    global_cmd->ret = exec_parent_built_ins(global_cmd->pid, cur_cmd);
    apply_redirections_out(cur_cmd);

    return (1);
}

int     is_built_in(char **cmd)
{
    if (!ft_strcmp(cmd[0], "echo") ||
        !ft_strcmp(cmd[0], "cd") ||
        !ft_strcmp(cmd[0], "env") ||
        !ft_strcmp(cmd[0], "pwd") ||
        !ft_strcmp(cmd[0], "exit") ||
        !ft_strcmp(cmd[0], "unset") ||
        !ft_strcmp(cmd[0], "export")
    )
        return (1);
    return (0);
}

void    exec(t_command *global_cmd, t_list_cmd  *cmds)
{
    char        **cmd;
    while (cmds != NULL)
    {
        cmd = extract_command_and_args(cmds->content);
		//printf("\nCMD[0] EXEC [[%s]]\n", cmd[0]);
		//printf("\nCMD[1] EXEC [[%s]]\n", cmd[1]);
        if (cmd[0] == 0)
		    global_cmd->ret = 127;
        if(open_redirections(cmds) == -1)
            return;
        // if(open_pipe(cmds) == -1)
        //     return;
	    if (is_built_in(cmd))
            exec_built_ins(global_cmd, cmd, cmds->content);
        else
            exec_command(cmds->content, global_cmd);
        //close_pipe(cmds);
        // close_redirections(cmds);
        cmds = cmds->next;
    }
}

