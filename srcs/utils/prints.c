#include "minishell.h"

void    print_strs(char **strs)
{
    while (*strs != NULL)
    {
        ft_printf("%s\n", *strs);
        strs++;
    }
}

void    print_cmd(t_command *cmd)
{
    if (cmd == NULL)
        return;
    ft_printf("Exec: %s\n", cmd->exec);
}

void print_cmds(t_command *cmd)
{
    while (cmd != NULL)
    {
        print_cmd(cmd);
        cmd = cmd->next;
    }
}