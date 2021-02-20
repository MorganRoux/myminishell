#include "minishell.h"

int    pwd(t_command *global_command, t_command *cmd)
{
    (void)cmd;
    char    *cwd;

    cwd = getcwd(NULL, 0);
    ft_printf("%s\n", cwd);
    free(cwd);
    return (0);
}