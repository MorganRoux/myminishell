#include "minishell.h"

enum    PATH_TYPE
{
        ABSOLUTE,
        RELATIVE,
        CURRENT,
        NONE,
        ERROR,
        BACK
};

char    *check_and_extract_cd_argument(t_command *cmd)
{
    if (ft_lstsize(cmd->args) != 1)
        return (NULL);
    return (ft_strdup(ft_lstof(cmd->args, 0)->content));
}

int     check_path_type(char *dir)
{
    (void)dir;
    return ABSOLUTE;
}

char     *build_full_path(char *new_dir, int path_type)
{
    (void)path_type;
    return (new_dir);
}

char    *replace_tilde(char *new_dir, t_command *global_command)
{
    char    *ret;
    char    *home;

    home = get_var(global_command->env_arr, "HOME");
    ret = ft_strjoin(home, ++new_dir);
    free(--new_dir);
    free(home);
    return (ret);
}

void    cd(t_command *global_command, t_command *cmd)
{
    char    *new_dir;

    if ((new_dir = check_and_extract_cd_argument(cmd)) == NULL)
    {
        ft_printf("error");
        return;
    }
    if(new_dir[0] == '~')
        new_dir = replace_tilde(new_dir, global_command);
    if (chdir(new_dir) == -1)
        ft_printf("error\n");
    free(new_dir);
    global_command->ret = 0;
}