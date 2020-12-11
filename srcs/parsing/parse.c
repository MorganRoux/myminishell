#include "minishell.h"

char        **split_pipes(char *line)
{
    char    **strs;
    
    strs = ft_split(line,  '|');
    return strs;
}

char        *check_exec(char *str, t_command *cmd)
{
    cmd->exec = str;
    return str;
}

t_command   *parse_commands(char **cmd_strs)
{
    char *str;
    t_command   *new;
    t_command   *cmds;

    cmds = NULL;
    str = NULL;
    while (*cmd_strs != NULL)
    {
        new =  ft_lstnew();
        str = *cmd_strs;
        // ft_printf("!%s", str);
        str = check_redirs(str, new);
        str = check_args(str, new);
        str = check_exec(str, new);
        ft_lstadd_back(&cmds, new);
        cmd_strs++;
    }
    return cmds;
}

t_command   *parse(char *line)
{
    char        **cmd_strs;
    t_command   *cmds;

    cmd_strs = NULL;
    cmds = NULL;
    if ((cmd_strs = split_pipes(line)) == NULL)
        return NULL;
    if ((cmds = parse_commands(cmd_strs)) == NULL)
        return NULL;
    print_cmds(cmds);
    return cmds;
}