#include "minishell.h"

t_command	g_globstruct;
//____________________________________________________
//handling ? / num / replacement

//____________________________________________________


int         solve_dquotes(char **str,  char **content)
{
    (*content)++;
    while (**content != '"')
    {
        if (**content == 0)
            return (-1);
        if (**content == '\\' && (
            *(*content + 1) == '$' || *(*content + 1) == '`' ||
            *(*content + 1) == '"' || *(*content + 1) == '!'
        ))
        {
            (*content)++;
            *(*str)++ = *(*content)++;
        }
        else
            *(*str)++ = *(*content)++;
    }
    (*content)++;
    return (0);
}

int         solve_squotes(char **str, char **content)
{
    (*content)++;
    while (**content !='\'')
    {
        if (**content == 0)
            return (-1);
        *(*str)++ = *(*content)++;
    }
    (*content)++;
    return (0);
}

int         solve_escape(char **str, char **content)
{
    (void)str;
    (*content)++;
    return (1);
}

int         solve_word(char **str, char **content)
{
    *(*str)++ = *(*content)++;
    return (0);
}

char        *solve_quotings(char *content)
{
    static  int escape = 0;
    char    *str;
    char    *ret;

    if(!(ret = (char *)malloc(ft_strlen(content) + 1)))
        return (NULL);
    str = ret;
    while (*content != 0)
    {
        if (*content == '"' && escape == 0)
            solve_dquotes(&str, &content);
        else if (*content == '\'' && escape == 0)
            solve_squotes(&str, &content);
        else if (*content == '\\' && escape == 0)
            escape = solve_escape(&str, &content);
        else
            escape = solve_word(&str, &content);
    }
    *str = 0;
    return (ret);
}

char    *extract_var_name(char *str)
{
    int     i;
    char    *name;

    str++;
    // ft_printf("\nstr=%s", str);
    i = 0;
    while(str[i] != 0 && ft_isalnum(str[i]) == 1)
        i++;
    // ft_printf("\ni=%d", i);
    if (!(name = (char *) malloc(sizeof(char) * (i + 1))))
        return (NULL);
    ft_strlcpy(name, str, i + 1);
    return (name);
}

int     replace_var(char **str, char **start, t_command *global_command)
{
    char    *var_name;
    char    *var_value;
    char    *new;

    var_name = extract_var_name(*str);
    var_value = get_var(global_command->env_arr, var_name);
    if (!(new = (char *) malloc(sizeof(char) * (ft_strlen(*start) - ft_strlen(var_name + 1) + ft_strlen(var_value)))))
        return (-1);
    
    ft_strlcpy(new, *start, *str  - *start + 1);
    ft_strlcat(new, var_value, ft_strlen(new) + ft_strlen(var_value) + 1);
    ft_strlcat(new, *str + (ft_strlen(var_name) + 1), ft_strlen(*start) + ft_strlen(var_value));

    // ft_printf("\n%d-%d-%d", ft_strlen(*start), (*str - *start), ft_strlen(var_value));
    *str = new + ((*str - *start)  + ft_strlen(var_value));
    // ft_printf("\niiii:%p-%p-%d\n", new, *str, (*str - new));
    // ft_printf("\n---\n%s-%s\n", new, *str);
    // getchar();
    free(*start);
    *start = new;
    free(var_value);
    free(var_name);
    return (0);
}

void    skip_squotes(char **str)
{
    int escape;

    escape = 0;
    (*str)++;
    while (**str != 0)
    {
        if (**str == '\\' && escape == 0)
            escape = 1;
        else if (**str == '\'' && escape == 0)
            return ;
        else if (escape == 1)
            escape = 0;
        (*str)++;
    }
}

char    *solve_dollards(char *str, t_command *global_command)
{
    int     escape;
    char    *start;

    start = str;
    escape = 0;
    while (*str != 0)
    {
        if (*str == '\\' && escape == 0)
            escape = 1;
        else if (*str == '$' && escape == 0)
            replace_var(&str, &start, global_command);
        else if (*str == '\'' && escape == 0)
            skip_squotes(&str);
        else if (escape == 1)
            escape = 0;
        str++;
    }
    // ft_printf("END:%s", start);
    // getchar();
    return (start);
    
    // if(ft_strcmp(str, "?") == 0)
    // {
    //     word = ft_itoa(global_command->ret);
    // }
    // else if ((word = get_var(global_command->env_arr, str)) == NULL)
    // {
    //     return (NULL);
    // }
    // return (word);
}

void        insert_word(t_list_cmd **cur, char *word, t_command *global_command)
{
    char        *str;
    t_command   *cmd;
    t_list_str  *arg;

    str = solve_dollards(word, global_command);
    str = solve_quotings(str);
    //printf("\nstr  = solve_quotings(word) [[%s]]\n", str);
    cmd = (*cur)->content;
    if (cmd->exec == NULL)
        cmd->exec = str;
    else
    {
        arg = ft_lstnew(str);
        ft_lstadd_back(&cmd->args, arg);
    }
}

t_list_str  *parse_fdin(t_list_str *tkn, t_list_cmd **cur)
{
    t_command   *cmd;
    t_list_str  *new;

    cmd = (*cur)->content;
    tkn = tkn->next;
    while (tkn != 0 && is_space_str(tkn->content))
        tkn = tkn->next;
    if (tkn == 0 || is_meta_str(tkn->content))
        return(NULL);
    new = ft_lstnew(solve_quotings(tkn->content));
    ft_lstadd_back(&cmd->files_in, new);
    return (tkn->next);
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
        return (NULL);
    new = ft_lstnew(solve_quotings(tkn->content));
    ft_lstadd_back(&cmd->files_out, new);
    return (tkn->next);
}

int         setup_pipe(t_list_cmd **cur)
{
    t_command   *cmd;

    cmd = (*cur)->content;
    if (!(cmd->pipe = malloc(2 * sizeof(int))))
        return (-1);
    pipe(cmd->pipe);
    return (0);
}

int         create_piped_command(t_list_cmd **cur)
{
    t_list_cmd  *new;
    t_command   *new_cmd;

    new = ft_lstinit();
    new_cmd = new->content;
    new_cmd->prev = (*cur)->content;
    (*cur)->next = new;
    *cur = new;
    return (0);
}

t_list_str  *parse_pipe(t_list_str *tkn, t_list_cmd **cur)
{
    if (setup_pipe(cur) == -1)
        return (NULL);
    create_piped_command(cur);
    return (tkn->next);
}

t_list_str  *parse_coma(t_list_str *tkn, t_list_cmd **cur)
{
    t_list_cmd  *new;

    new = ft_lstinit();
    (*cur)->next = new;
    *cur = new;
    return (tkn->next);
}


t_list_str  *parse_dollard(t_list_str *tkn, t_list_cmd **cur, t_command *global_command)
{
    char        *word;
    t_command   *cmd;

    cmd = (*cur)->content;
    tkn = tkn->next;
    if(ft_strcmp(tkn->content, "?") == 0)
    {
        word = ft_itoa(global_command->ret);
    }
    else if ((word = get_var(global_command->env_arr, tkn->content)) == NULL)
    {
        return (tkn->next);
    }
    insert_word(cur, word, global_command);
    return (tkn->next);
}

t_list_str  *parse_meta(t_list_str *tkn, t_list_cmd **cur, t_command *global_command)
{
    (void)global_command;
    if (ft_strcmp(tkn->content, " ") == 0)
        return (tkn->next);
    //else if (ft_strcmp(tkn->content, "=$") != 0)
    //    return (parse_dollard(tkn, cur, global_command));
    else if (ft_strcmp(tkn->content, "<") == 0)
        return (parse_fdin(tkn, cur));
    else if (ft_strcmp(tkn->content, ">") == 0)
        return (parse_fdout(tkn, cur));
    else if (ft_strcmp(tkn->content, "|") == 0)
        return (parse_pipe(tkn, cur));
    else if (ft_strcmp(tkn->content, ";") == 0)
        return (parse_coma(tkn, cur));
    // else if (ft_strcmp(tkn->content, "$") == 0)
    //     return (parse_dollard(tkn, cur, global_command));
    return (tkn->next);
}

t_list_str  *parse_word(t_list_str *tkn, t_list_cmd **cur, t_command *global_command)
{
    insert_word(cur, tkn->content, global_command);
    return (tkn->next);
}

t_list_cmd  *parse_tokens(t_list_str *tokens, t_command *global_command)
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
            tkn = parse_meta(tkn, &cur, global_command);
        else
            tkn = parse_word(tkn, &cur, global_command);
    }
    return (cmds);
}

t_list_cmd   *parse(char *line, t_command *global_command)
{
    t_list_cmd  *cmds;
    t_list_str  *tokens;

    cmds = NULL;
    tokens = split_tokens(line);
    cmds = parse_tokens(tokens, global_command);
    return (cmds);
}