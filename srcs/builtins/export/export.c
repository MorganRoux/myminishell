#include "minishell.h"

char    **delete_var(char *env[], int index)
{
    int     i;
    int     j;
    char    **new_env;

    i = 0;
    j = 0;
    if (!(new_env = malloc(sizeof(char *) * get_strs_len(env))))
        return NULL;
    while (i < get_strs_len(env))
    {
        if (i != index)
            new_env[j++] = ft_strdup(env[i]);
        i++;
    }
    new_env[j] = 0;
    return (new_env);
}

char    **delete_from_env(char *env[], char *var)
{
    int     index;
    char    **var_splitted;
    char    **new_env;

    var_splitted = ft_split(var, '=');
    index = get_var_index(env, var_splitted[0]);
    if (index == -1)
        new_env = env;
    else
    {
        new_env = delete_var(env, index);
        free_strs(env);
    }
    free_strs(var_splitted);
    return (new_env);
}

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

int     export(t_command *global_command, t_command *cmd)
{
    t_list_str  *args;

    if((args = cmd->args) == NULL)
        return (sorted_env(global_command->env_arr));
    while (args != NULL)
    {
        if (!check_export_arg(args->content))
            return (2);
        global_command->env_arr  = delete_from_env(global_command->env_arr, args->content);
        global_command->env_arr = add_to_env(global_command->env_arr, args->content);
        args = args->next;
    }
    return (0);
}