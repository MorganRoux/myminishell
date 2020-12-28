#include "minishell.h"

int     *open_fds(t_list_str *files, int  flag)
{
    char    *path;
    int     i;
    int     *fd;

    i = 0;
    if(!(fd = malloc(sizeof(int) * ft_lstsize(files))))
        return NULL;
    while (files != NULL)
    {
        path = files->content;
        fd[i] = open(path, flag);
        if (fd[i] < 0)
            return NULL;
        files = files->next;
        i++;
    }
    return fd;
}

int     open_redirections(t_list_cmd *cmd)
{
    t_command   *content;

    content = cmd->content;
    if (
        (content->fd_in = open_fds(content->files_in, O_RDONLY)) == NULL ||
        (content->fd_out = open_fds(content->files_out, O_WRONLY)) == NULL
    )
        return -1;

    return (0);
}

int     close_fds(int *fds, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        if (close(fds[i++]) == -1)
            return -1;
    }
    return 0;
}

int     close_redirections(t_list_cmd *cmd)
{
    t_command   *content;

    content = cmd->content;
    close_fds(content->fd_in, ft_lstsize(content->files_in));
    close_fds(content->fd_out, ft_lstsize(content->files_out));
    return (0);
}

int     apply_redirections_in(t_command *cmd)
{
    // test for just one file
    if (ft_lstsize(cmd->files_in) == 1)
    {
        dup2(cmd->fd_in[0], STDIN_FILENO);
        //close(cmd->fd_in[0]);
    }
    return (1);
}