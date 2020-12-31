#include "minishell.h"

int     open_pipe(t_list_cmd *cmd)
{
    (void)cmd;
    return (0);
}

int     close_pipe(t_list_cmd *cmd)
{
    t_command   *content;
    t_command   *prev;

    content = cmd->content;
    prev = content->prev;
    if (content->pipe != NULL)
        close(content->pipe[1]);
    if (prev != NULL)
        close(prev->pipe[0]);
    return (0);
}

int     apply_pipe_in(t_command *cmd)
{
    t_command  *prev = cmd->prev;

    close(prev->pipe[1]);
    dup2(prev->pipe[0], STDIN_FILENO);
    close(prev->pipe[0]);
    return (0);
}

int     apply_pipe_out(t_command *cmd)
{
    close(cmd->pipe[0]);
    dup2(cmd->pipe[1], STDOUT_FILENO);
    close(cmd->pipe[1]);
    return (0);
}

int     is_pipe_out(t_command *cmd)
{
    return (cmd->pipe == NULL ? 0 : 1);  
}

int     is_pipe_in(t_command *cmd)
{
    return (cmd->prev == NULL ? 0 : 1);
}

int     apply_pipes(t_command *cmd)
{
    if (is_pipe_out(cmd))
        apply_pipe_out(cmd);
    if (is_pipe_in(cmd))
        apply_pipe_in(cmd);
    return (1);
}