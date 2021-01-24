#include "minishell.h"

void    free_strs(char **strs)
{
    int i;

    i = 0;
    while(strs[i] != 0)
        free(strs[i++]);
    free(strs);
}

void    free_cmd(void *param)
{
    t_command   *cmd;

    cmd = (t_command *)param;
    free(cmd->exec);
    ft_lstclear(&cmd->args, free);
    ft_lstclear(&cmd->files_append, free);
    ft_lstclear(&cmd->files_out, free);
    ft_lstclear(&cmd->files_in, free);
    free(cmd->pipe);
    free(cmd->fd_in);
    free(cmd->fd_out);
    //free(cmd->flux_in);
    //free(cmd->flux_out);
    free(cmd);
}
void    free_cmds(t_list_cmd *cmds)
{
    ft_lstclear(&cmds, &free_cmd);
    free(cmds);
}