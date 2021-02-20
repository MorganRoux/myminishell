#include "minishell.h"

void    pwd(t_command *global_command, t_command *cmd)
{
    (void)cmd;
    ft_printf("%s\n", getcwd(NULL, 0));
    global_command->ret = 0;
}