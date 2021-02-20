#include "minishell.h"

void    do_exit(t_command *global_command, t_command *cmd)
{
    (void)cmd;

    if (global_command->ret != 0)
        errno = global_command->ret;
    ft_printf("exit\n");
    exit(errno);
}