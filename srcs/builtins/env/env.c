#include "minishell.h"

int    env(t_command *global_command, t_command *cmd)
{
    char    **env;

    (void)cmd;
    env = global_command->env_arr;
    if (env == NULL)
        return (0);
    while (*env != NULL)
    {
        ft_printf("%s\n", *env);
        env++;
    }
    return (0);
}