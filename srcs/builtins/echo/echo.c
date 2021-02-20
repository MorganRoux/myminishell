#include "minishell.h"

int     is_option_n(t_list_str *args)
{
    return (ft_strcmp(args->content, "-n") == 0 ? 1 : 0);
}

void    echo(t_command *global_command, t_command *cmd)
{
    t_list_str  *args;
    int         option_n;

    option_n = 0;
    global_command->ret = 0;
    if ((args = cmd->args) == NULL)
        return;
    if (is_option_n(args))
    {
        option_n = 1;
        args = args->next;
    }
    while (args != NULL)
    {
        ft_printf(args->content);
        args = args->next;
        if (args != NULL)
            ft_printf(" "); 
    }
    if (option_n == 0)
        ft_printf("\n");
    return ;
}