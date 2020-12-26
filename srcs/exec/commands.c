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

    if ((pid = fork()) < 0) 
        return -1;
    else if (pid == 0)
    {
        dup2(cmd->fd_in[0], STDIN_FILENO);
        close(cmd->fd_in[0]);
        execve(bin, params, envp);
        return -1;
    }
    close(cmd->fd_in[0]);
    waitpid(pid, &status, 0);
    free(bin);
    return (1);
}