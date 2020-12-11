#include "minishell.h"

char        **split_pipes(char *line)
{
    char    **strs;

    strs = ft_split(line,  '|');
    return strs;
}

char        *get_next_token(char **line)
{
    char *tkn;
    char *start;
    int i;
    char *ret;

    if (**line == 0)
        return NULL;
    tkn =  malloc(1);
    tkn[0] = 0;
    i = 1;
    start = *line;
    while (**line != ' ' && **line != 0)
    {
        (*line)++;
        i++;
    }
    tkn = ft_strnjoin(tkn, start, i);
    if (**line != 0)
        (*line)++;
    ret = ft_strtrim(tkn, " ");
    free(tkn);
    return ret;
}

int         count_commands(char *line)
{
    char    *tkn;
    int     i;

    i = 1;
    while  ((tkn = get_next_token(&line)) != NULL)
    {
        if (ft_strcmp(tkn,"|") == 0 || ft_strcmp(tkn, ";") == 0)      //TODO : ';' terminate the line
            i++;
        free(tkn);
    }
    return i;
}

char         **allow_command(char *line)
{
    char    **strs;
    int     n_cmd;
    int     i;

    i = 0;
    n_cmd  = count_commands(line);
    // printf("ncomnd %d", n_cmd);
    // getchar();
    if  (!(strs = malloc((n_cmd + 1) * sizeof(char *))))
        return  NULL;
    while (i < n_cmd)
    {
        if  (!(strs[i] = malloc(sizeof(char))))
            return  NULL;
        *(strs[i]) = 0;
        i++;
    }
    strs[i] = NULL;
    return strs;
    
}

char        **split_commands(char *line)
{
    char    **strs;
    char    *tkn;
    int     i;
    char    *start;

    i = 0;
    strs = allow_command(line);
    start = line;
    while  ((tkn = get_next_token(&line)) != NULL)
    {
        if (ft_strcmp(tkn,"|")  == 0 || ft_strcmp(tkn, ";") == 0)
        {
            strs[i] = ft_substr(start, 0, line - start);
            start = line;
            i++;
        }
        free(tkn);
    }
    strs[i] = ft_substr(start, 0, line - start);
    return strs;
}

void        analyse_command(char *str, t_command *cmd)
{
    char    *tkn;

    cmd->exec = str;

    while ((tkn = get_next_token(&str)) != NULL)
    {

        free(tkn);
    }
}

char        *check_exec(char *str, t_command *cmd)
{
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
        // str = check_redirs(str, new);
        // str = check_args(str, new);
        // str = check_exec(str, new);
        analyse_command(str, new);
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
    if ((cmd_strs = split_commands(line)) == NULL)
        return NULL;
    if ((cmds = parse_commands(cmd_strs)) == NULL)
        return NULL;
    print_cmds(cmds);
    return cmds;
}