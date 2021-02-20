#include "minishell.h"

void    echo(t_command *global_command, t_command *cmd)
{
    t_list_str  *args;
    (void)global_command;

    args = cmd->args;
    while (args != NULL)
    {
        ft_printf(args->content);
        args = args->next;
        if (args != NULL)
            ft_printf(" ");
    }
    ft_printf("\n");
    return ;
}