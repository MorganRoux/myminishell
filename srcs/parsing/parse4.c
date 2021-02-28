/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:14:47 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/09 13:14:31 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*solve_dollards(char *str)
{
	int		escape;
	char	*start;

	start = str;
	escape = 0;
	while (*str != 0)
	{
		if (*str == '\\' && escape == 0)
			escape = 1;
		else if (*str == '$' && escape == 0)
			replace_var(&str, &start);
		else if (*str == '\'' && escape == 0)
			skip_squotes(&str);
		else if (escape == 1)
			escape = 0;
		str++;
	}
	return (start);
}

void		insert_word(t_list_cmd **cur, char *word)
{
	char		*str;
	t_command	*cmd;
	t_list_str	*arg;

	str = ft_strdup(word);
	str = solve_quotings(str);
	cmd = (*cur)->content;
	if (cmd->exec == NULL)
		cmd->exec = str;
	else
	{
		arg = ft_lstnew(str);
		ft_lstadd_back(&cmd->args, arg);
	}
}

t_list_str	*parse_fdout(t_list_str *tkn, t_list_cmd **cur)
{
	t_command	*cmd;
	t_list_str	*new;
	char		*redir;
	char		*str;

	redir = tkn->content;
	cmd = (*cur)->content;
	tkn = tkn->next;
	while (tkn != 0 && is_space_str(tkn->content))
		tkn = tkn->next;
	if (tkn == 0 || is_meta_str(tkn->content))
		return (NULL);
	str = ft_strdup(tkn->content);
	new = ft_lstnew(solve_quotings(str));
	if (ft_strcmp(redir, ">") == 0)
		ft_lstadd_back(&cmd->files_out, new);
	else
		ft_lstadd_back(&cmd->files_append, new);
	return (tkn->next);
}

int			setup_pipe(t_list_cmd **cur)
{
	t_command	*cmd;

	cmd = (*cur)->content;
	if (!(cmd->pipe = malloc(2 * sizeof(int))))
		return (-1);
	return (pipe(cmd->pipe));
}

int			create_piped_command(t_list_cmd **cur)
{
	t_list_cmd	*new;
	t_command	*new_cmd;

	new = ft_lstinit();
	new_cmd = new->content;
	new_cmd->prev = (*cur)->content;
	(*cur)->next = new;
	*cur = new;
	return (0);
}
