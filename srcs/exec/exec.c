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

char    *find_bin(char *bin, char *envp[])
{
    char    *full_bin;
    char    **paths;
    int     i;

    i = 0;
    paths = get_paths(envp);
    full_bin = ft_strjoin(paths[0], bin);
    while( open(full_bin, O_RDONLY) == -1)
    {
        free(full_bin);
        if (paths[++i] == 0)
            return ft_strdup(bin);
        full_bin = ft_strjoin(paths[i], bin);
    }
    free_strs(paths);
    free(paths);
    return full_bin;
}

int     exec_command(t_command *cmd, char *envp[])
{
    char    **params;
    char    *bin;
    int     pid;
    int     status;

    if (cmd->exec == NULL)
        return (1);
    bin = find_bin(cmd->exec, envp);
    params = cmd2char(cmd);
    pid = fork();
    if (pid == 0)
    {
        execve(bin, params, envp);
        return (0);
    }
    else
        waitpid(pid, &status, 0);
    free(bin);
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

void    exec2(t_command *mimi, t_list_cmd  *commands, char *envp[])
{
    t_list_cmd  *cmds;
    char        **cmd;

    cmds = commands;
    while (cmds != NULL)
    {
        cmd = cmd2char(cmds->content);
        if (cmd[0] == 0)
		    mimi->ret = 127;
	    if (exec_built_ins(mimi, cmd) != 1)
            exec_command(cmds->content, envp);
        cmds = cmds->next;
    }
}

