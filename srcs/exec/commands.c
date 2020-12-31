#include "minishell.h"

/**
 * find_bin()
 * Search the command in all the paths from the PATH env variable.
 * If not found, return the command
 * If found, return the whole path of the command
 * */
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

void    exec_child(t_command *cmd, char *envp[], char *bin, char **params)
{
    
    
    dup2(cmd->flux_in[0], STDIN_FILENO);
    close(cmd->flux_in[0]);
    close(cmd->flux_in[1]);
    
    execve(bin, params, envp);
}

void    exec_parent(int pid, char *bin, t_command *cmd)
{
    
    close(cmd->flux_in[0]);
    close(cmd->flux_in[1]);
    waitpid(pid, &(cmd->status), 0);
    free(bin);
    
}

int     exec_command(t_command *cmd, char *envp[])
{
    char    **params;
    char    *bin;
    int     pid;

    if (cmd->exec == NULL)
        return (1);
    bin = find_bin(cmd->exec, envp);
    params = extract_command_and_args(cmd);
    apply_redirections(cmd);
    apply_pipes(cmd);
    if ((pid = fork()) < 0) 
        return -1;
    else if (pid == 0)
        exec_child(cmd, envp, bin, params);
    exec_parent(pid, bin, cmd);
    return (1);
}