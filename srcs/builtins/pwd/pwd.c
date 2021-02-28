#include "minishell.h"

int    pwd(t_command *cmd)
{
    (void)cmd;
    char    *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        ft_printf("erreur");
        return (2);
    }
    ft_printf("%s\n", cwd);
    free(cwd);
    return (0);
}