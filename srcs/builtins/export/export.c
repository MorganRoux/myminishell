#include "minishell.h"

char    **add_to_env(char *env[], char *var)
{
    int     len;
    char    **new_env;
    int     i;

    i = -1;
    len = get_strs_len(env);
    if (!(new_env = (char **) malloc(sizeof(char **) * (len + 2))))
        return env;
    while (++i < len)
        new_env[i] = env[i];
    new_env[i++] = ft_strdup(var);
    new_env[i] = 0;
    free(env);
    return (new_env);
}

int     check_export_arg(char *arg)
{
    (void)arg;
    return (1);
}

void    export(t_command *global_command, t_command *cmd)
{
    t_list_str  *args;

    if((args = cmd->args) == NULL)
        return ;
    while (args != NULL)
    {
        if (!check_export_arg(args->content))
            return ;
        global_command->env_arr = add_to_env(global_command->env_arr, args->content);
        args = args->next;
    }
}