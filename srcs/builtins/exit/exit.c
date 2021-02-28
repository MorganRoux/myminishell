#include "minishell.h"

void    exit_arg(t_list_str *arg)
{
    if ((ft_atoi(arg->content) == 0) && ((char *)(arg->content))[0] != '0')
    {
        ft_putstr_fd("exit: argument numérique nécessaire", 2);
        exit(2);
    }
    exit(ft_atoi(arg->content));
}
void    do_exit(t_command *cmd)
{
    (void)cmd;

    ft_putstr_fd("exit\n", 2);
    if (ft_lstsize(cmd->args) > 1)
    {
        ft_putstr_fd("exit: too many arguments", 2);
        exit(1);
    }
    else if (ft_lstsize(cmd->args) == 1)
        exit_arg(cmd->args);
    else
    {
        if (g_globstruct.ret == 0)
        exit(0);
        errno = g_globstruct.ret;
        exit(errno);
    }
}