#include "minishell.h"

char    **unset_from_env(char *env[], int index)
{
    char    **new_env;
    int     i;
    int     j;
    int     len;

    i = 0;
    j = 0;
    
    if ((len = get_strs_len(env)) == -1)
        return (NULL);
    if (!(new_env = (char **) malloc(sizeof(char *) * len)))
        return (NULL);
    while (i < len)
    {
        if (i != index)
        {
            new_env[j] = strdup(env[i]);
            j++;
        }
        i++;
    }
    new_env[j] = NULL;
    free_strs(env);
    return (new_env);


}
void    unset(t_command *global_command, t_command *cmd)
{
    t_list_str  *args;
    int        index;

    if ((args = cmd->args) == NULL)
        return;
    while (args != NULL)
    {
        index = get_var_index(global_command->env_arr, args->content);
        if (index != -1)
            global_command->env_arr = unset_from_env(global_command->env_arr, index);
        args = args->next;
    }
}