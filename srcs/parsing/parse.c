#include "minishell.h"

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