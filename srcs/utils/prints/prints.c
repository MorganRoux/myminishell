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
    t_list_str  *args;

    i = 0;
    if (cmd == NULL)
        return;
    ft_printf("Exec:%s:\n", cmd->exec);
    args = cmd->args;
    while (args != 0)
    {
        ft_printf("Arg%d:%s:\n", i, args->content);
        args = args->next;
        i++;
    }
}

void print_cmds(t_list_cmd *cmd)
{
    while (cmd != NULL)
    {
        print_cmd(cmd->content);
        cmd = cmd->next;
    }
}