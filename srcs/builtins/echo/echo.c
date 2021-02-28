#include "minishell.h"

int     check_option_n(t_list_str **args)
{
    if (ft_strcmp((*args)->content, "-n") != 0)
        return (0);
    while(args != 0 && ft_strcmp((*args)->content, "-n") == 0)
        *args = (*args)->next;
    return (1);
}

int    echo(t_command *global_command, t_command *cmd)
{
    t_list_str  *args;
    int         option_n;

    option_n = 0;
    global_command->ret = 0;
    if ((args = cmd->args) == NULL)
    {
        ft_printf("\n");
        return (0);
    }  
    if (check_option_n(&args))
        option_n = 1;
    while (args != NULL)
    {
        ft_printf(args->content);
        args = args->next;
        if (args != NULL)
            ft_printf(" "); 
    }
    if (option_n == 0)
        ft_printf("\n");
    return (0);
}