#include "minishell.h"

void    env(t_command *global_command, t_command *cmd)
{
    char    **env;

    (void)cmd;
    env = global_command->env_arr;
    if (env == NULL)
        return ;
    while (*env != NULL)
    {
        ft_printf("%s\n", *env);
        env++;
    }
    global_command->ret = 0;
    return ;
}