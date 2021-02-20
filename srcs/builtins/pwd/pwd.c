#include "minishell.h"

void    pwd(t_command *global_command, t_command *cmd)
{
    (void)cmd;
    char    *cwd;

    cwd = getcwd(NULL, 0);
    ft_printf("%s\n", cwd);
    free(cwd);
    global_command->ret = 0;
}