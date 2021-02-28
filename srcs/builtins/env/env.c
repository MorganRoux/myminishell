#include "minishell.h"

int     sorted_env(char **env)
{
    char    **sorted;
    int     i;

    i = 0;
    sorted = duplicate_strs(env);
    ft_sort_string_tab(sorted);
    if (sorted == NULL)
        return (0);
    while (sorted[i] != NULL)
        ft_printf("%s\n", sorted[i++]);
    free_strs(sorted);
    return (0);
}

int     env(t_command *cmd)
{
    char    **env;

    (void)cmd;
    env = g_globstruct.env_arr;
    if (env == NULL)
        return (0);
    while (*env != NULL)
    {
        ft_printf("%s\n", *env);
        env++;
    }
    return (0);
}