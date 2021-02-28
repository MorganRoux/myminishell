#include "minishell.h"

char    *check_and_extract_cd_argument(t_command *cmd)
{
    if (ft_lstsize(cmd->args) != 1)
        return (NULL);
    return (ft_strdup(ft_lstof(cmd->args, 0)->content));
}


char    *replace_tilde(char *new_dir)
{
    char    *ret;
    char    *home;

    home = get_var(g_globstruct.env_arr, "HOME");
    ret = ft_strjoin(home, ++new_dir);
    free(--new_dir);
    free(home);
    return (ret);
}

int    cd(t_command *cmd)
{
    char    *new_dir;
    if (cmd->args == NULL)
        return 0;    
    if ((new_dir = check_and_extract_cd_argument(cmd)) == NULL)
    {
        ft_printf("error");
        return (2);
    }
    if(new_dir[0] == '~')
        new_dir = replace_tilde(new_dir);
    if (chdir(new_dir) == -1)
    {
        free(new_dir);
        ft_printf("error\n");
        return (2);
    }
    free(new_dir);
    return (0);
}