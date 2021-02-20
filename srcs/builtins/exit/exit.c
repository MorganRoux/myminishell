#include "minishell.h"

void    do_exit(t_command *global_command, t_command *cmd)
{
    (void)cmd;

    //ft_printf("exit\n");
    if (global_command->ret == 0)
        exit(0);
    errno = global_command->ret;
    exit(errno);
}