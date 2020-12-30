#include "minishell.h"

int     open_pipe(t_list_cmd *cmd)
{
    (void)cmd;
    return (0);
}

int     close_pipe(t_list_cmd *cmd)
{
    (void)cmd;
    return (0);
}

int     apply_pipes_in(t_command *cmd)
{
    t_command  *prev = cmd->prev;

    close(prev->pipe[1]);
    dup2(prev->pipe[0], STDIN_FILENO);
    close(prev->pipe[0]);
    return (0);
}

int     apply_pipes_out(t_command *cmd)
{
    close(cmd->pipe[0]);
    dup2(cmd->pipe[1], STDOUT_FILENO);
    close(cmd->pipe[1]);
    return (0);
}

int     apply_pipes(t_command *cmd)
{
    if (cmd->pipe != NULL)
        apply_pipes_out(cmd);
    if (cmd->prev != NULL)
        apply_pipes_in(cmd);
    return (1);
}