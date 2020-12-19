#include "minishell.h"

void    print_strs(char **strs)
{
    while (*strs != NULL)
    {
        ft_printf(":%s:\n", *strs);
        strs++;
    }
}

void    print_lst_str(t_list_str *strs)
{
    while (strs != NULL)
    {
        ft_printf(":%s:\n", strs->content);
        strs = strs->next;
    }
}

void    print_cmd(t_command *cmd)
{
    int i;
    t_list_str  *lst;
    t_command   *pipe;
    if (cmd == NULL)
        return;
    ft_printf("\n-----\nExec:%s:\n", cmd->exec);
    i = 0;
    lst = cmd->args;
    while (lst != 0)
    {
        ft_printf("Arg%d:%s:\n", i, lst->content);
        lst = lst->next;
        i++;
    }
    i = 0;
    lst = cmd->fd_in;
    while (lst != 0)
    {
        ft_printf("Fdin%d:%s:\n", i, lst->content);
        lst = lst->next;
        i++;
    }
    i = 0;
    lst = cmd->fd_out;
    while (lst != 0)
    {
        ft_printf("Fdout%d:%s:\n", i, lst->content);
        lst = lst->next;
        i++;
    }
    pipe = cmd->pipe;
    if (pipe != 0)
        ft_printf("Pipe to:%s:\n", pipe->exec);

    ft_printf("-----\n");
}

void print_cmds(t_list_cmd *cmd)
{
    while (cmd != NULL)
    {
        print_cmd(cmd->content);
        cmd = cmd->next;
    }
}