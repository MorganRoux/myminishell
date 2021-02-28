/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:14:54 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/09 10:20:03 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_str	*parse_pipe(t_list_str *tkn, t_list_cmd **cur)
{
	(void)cur;
	if (setup_pipe(cur) == -1)
		return (NULL);
	return (tkn->next);
}

t_list_str	*parse_coma(t_list_str *tkn, t_list_cmd **cur)
{
	t_list_cmd	*new;

	(void)new;
	(void)cur;
	return (tkn->next);
}

t_list_str	*parse_meta(t_list_str *tkn, t_list_cmd **cur)
{
	if (ft_strcmp(tkn->content, " ") == 0)
		return (tkn->next);
	else if (ft_strcmp(tkn->content, "<") == 0)
		return (parse_fdin(tkn, cur));
	else if (ft_strcmp(tkn->content, ">") == 0
			|| ft_strcmp(tkn->content, ">>") == 0)
		return (parse_fdout(tkn, cur));
	else if (ft_strcmp(tkn->content, "|") == 0)
		return (parse_pipe(tkn, cur));
	else if (ft_strcmp(tkn->content, ";") == 0)
		return (parse_coma(tkn, cur));
	return (tkn->next);
}

t_list_str	*parse_word(t_list_str *tkn, t_list_cmd **cur)
{
	insert_word(cur, tkn->content);
	return (tkn->next);
}

t_list_cmd	*parse_tokens(t_list_str *tokens)
{
	t_list_cmd	*cmds;
	t_list_cmd	*cur;
	t_list_str	*tkn;

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
	return (cmds);
}
