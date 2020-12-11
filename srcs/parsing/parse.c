#include "minishell.h"

char        **split_pipes(char *line)
{
    char    **strs;
    
    strs = ft_split(line,  '|');
    return strs;
}

int         check_syntax(char  **cmd)
{
    (void) cmd;
    return 0;
}

t_command   *parse(char *line)
{
    char    **cmd_strs;

    cmd_strs = NULL;
    if ((cmd_strs = split_pipes(line)) == NULL)
        return NULL;
    
    print_strs(cmd_strs);
    return NULL;
}