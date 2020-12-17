#include "minishell.h"

// char        **split_pipes(char *line)
// {
//     char    **strs;

//     strs = ft_split(line,  '|');
//     return strs;
// }

// char        *get_next_token(char **line)
// {
//     char *tkn;
//     char *start;
//     int i;
//     char *ret;

//     if (**line == 0)
//         return NULL;
//     tkn =  malloc(1);
//     tkn[0] = 0;
//     i = 1;
//     start = *line;
//     while (**line != ' ' && **line != 0)
//     {
//         (*line)++;
//         i++;
//     }
//     tkn = ft_strnjoin(tkn, start, i);
//     if (**line != 0)
//         (*line)++;
//     ret = ft_strtrim(tkn, " ");
//     free(tkn);
//     return ret;
// }

// int         count_commands(char *line)
// {
//     char    *tkn;
//     int     i;

//     i = 1;
//     while  ((tkn = get_next_token(&line)) != NULL)
//     {
//         if (ft_strcmp(tkn,"|") == 0 || ft_strcmp(tkn, ";") == 0)      //TODO : ';' terminate the line
//             i++;
//         free(tkn);
//     }
//     return i;
// }

// char         **allow_command(char *line)
// {
//     char    **strs;
//     int     n_cmd;
//     int     i;

//     i = 0;
//     n_cmd  = count_commands(line);
//     // printf("ncomnd %d", n_cmd);
//     // getchar();
//     if  (!(strs = malloc((n_cmd + 1) * sizeof(char *))))
//         return  NULL;
//     while (i < n_cmd)
//     {
//         if  (!(strs[i] = malloc(sizeof(char))))
//             return  NULL;
//         *(strs[i]) = 0;
//         i++;
//     }
//     strs[i] = NULL;
//     return strs;
    
// }

// char        **split_commands(char *line)
// {
//     char    **strs;
//     char    *tkn;
//     int     i;
//     char    *start;

//     i = 0;
//     strs = allow_command(line);
//     start = line;
//     while  ((tkn = get_next_token(&line)) != NULL)
//     {
//         if (ft_strcmp(tkn,"|")  == 0 || ft_strcmp(tkn, ";") == 0)
//         {
//             strs[i] = ft_substr(start, 0, line - start);
//             start = line;
//             i++;
//         }
//         free(tkn);
//     }
//     strs[i] = ft_substr(start, 0, line - start);
//     return strs;
// }

// void        analyse_command(char *str, t_command *cmd)
// {
//     char    *tkn;

//     cmd->exec = str;

//     while ((tkn = get_next_token(&str)) != NULL)
//     {

//         free(tkn);
//     }
// }

// char        *check_exec(char *str, t_command *cmd)
// {
//     (void) cmd;
//     return str;
// }

// t_list   *parse_commands(char **cmd_strs)
// {
//     char *str;
//     t_list   *new;
//     t_list   *cmds;

//     cmds = NULL;
//     str = NULL;
//     while (*cmd_strs != NULL)
//     {
//         new =  ft_lstinit();
//         str = *cmd_strs;
//         // str = check_redirs(str, new);
//         // str = check_args(str, new);
//         // str = check_exec(str, new);
//         analyse_command(str, new->content);
//         ft_lstadd_back(&cmds, new);
//         cmd_strs++;
//     }
//     return cmds;
// }

t_list_str  *parse_fdin(t_list_str *tkn, t_list_cmd **cur)
{
    t_command   *cmd;
    t_list_str  *new;

    cmd = (*cur)->content;
    tkn = tkn->next;
    while (tkn != 0 && is_space_str(tkn->content))
        tkn = tkn->next;
    if (tkn == 0 || is_meta_str(tkn->content))
        return NULL;
    new = ft_lstnew(tkn->content);
    ft_lstadd_back(&cmd->fd_in, new);
    return tkn->next;
}

t_list_str  *parse_fdout(t_list_str *tkn, t_list_cmd **cur)
{
    t_command   *cmd;
    t_list_str  *new;

    cmd = (*cur)->content;
    tkn = tkn->next;
    while (tkn != 0 && is_space_str(tkn->content))
        tkn = tkn->next;
    if (tkn == 0 || is_meta_str(tkn->content))
        return NULL;
    new = ft_lstnew(tkn->content);
    ft_lstadd_back(&cmd->fd_out, new);
    return tkn->next;
}

t_list_str  *parse_pipe(t_list_str *tkn, t_list_cmd **cur)
{
    t_list_cmd  *new;
    t_command   *cmd;

    new = ft_lstinit();
    cmd = new->content;
    cmd->pipe = (*cur)->content;
    (*cur)->next = new;
    *cur = new;
    return tkn->next;
}

t_list_str  *parse_meta(t_list_str *tkn, t_list_cmd **cur)
{
    if (ft_strcmp(tkn->content, " ") == 0)
        return tkn->next;
    else if (ft_strcmp(tkn->content, "<") == 0)
        return parse_fdin(tkn, cur);
    else if (ft_strcmp(tkn->content, ">") == 0)
        return parse_fdout(tkn, cur);
    else if (ft_strcmp(tkn->content, "|") == 0)
        return parse_pipe(tkn, cur);
    return tkn->next;
}

t_list_str  *parse_word(t_list_str *tkn, t_list_cmd **cur)
{
    t_command   *cmd;
    t_list_str  *arg;

    cmd = (*cur)->content;
    if (cmd->exec == NULL)
        cmd->exec = ft_strdup(tkn->content);
    else
    {
        arg = ft_lstnew(ft_strdup(tkn->content));
        ft_lstadd_back(&cmd->args, arg);
    }
 
    return tkn->next;
}

t_list_cmd  *parse_tokens(t_list_str *tokens)
{
    t_list_cmd  *cmds;
    t_list_cmd  *cur;
    t_list_str  *tkn;

    cmds = ft_lstinit();
    cur = cmds;
    tkn = tokens;
    while (tkn != 0)
    {
        if (is_meta_str(tkn->content))
            tkn = parse_meta(tkn, &cur);
        else
            tkn = parse_word(tkn, &cur);
    }
    return cmds;
}

t_list_cmd   *parse(char *line)
{
    t_list_cmd  *cmds;
    t_list_str  *tokens;
    cmds = NULL;

    tokens = split_tokens(line);
    cmds = parse_tokens(tokens);
    return cmds;
}