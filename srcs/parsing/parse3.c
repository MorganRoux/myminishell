/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:14:42 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/09 13:12:54 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_str	*parse_fdin(t_list_str *tkn, t_list_cmd **cur)
{
	t_command	*cmd;
	t_list_str	*new;
	char		*str;

	cmd = (*cur)->content;
	tkn = tkn->next;
	while (tkn != 0 && is_space_str(tkn->content))
		tkn = tkn->next;
	if (tkn == 0 || is_meta_str(tkn->content))
		return (NULL);
	str = ft_strdup(tkn->content);
	new = ft_lstnew(solve_quotings(str));
	ft_lstadd_back(&cmd->files_in, new);
	return (tkn->next);
}

char		*extract_var_name(char *str)
{
	int		i;
	char	*name;

	str++;
	i = 0;
	if (*str == '?')
	{
		name = ft_strdup("?");
		return (name);
	}
	while (str[i] != 0 && ft_isalnum_u(str[i]) == 1)
		i++;
	if (!(name = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	return (name);
}

char		*do_replace(char **start, char **str)
{
	char	*var_name;
	char	*var_value;
	char	*new;

	var_name = extract_var_name(*str);
	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(g_globstruct.ret);
	else
		var_value = get_var(g_globstruct.env_arr, var_name);
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(*start)
				- ft_strlen(var_name) + 1 + ft_strlen(var_value)))))
		return (NULL);
	ft_strlcpy(new, *start, *str - *start + 1);
	ft_strlcat(new, var_value, ft_strlen(new)
				+ ft_strlen(var_value) + 1);
	ft_strlcat(new, *str + (ft_strlen(var_name) + 1),
				ft_strlen(*start) + ft_strlen(var_value));
	*str = new + ((*str - *start) + ft_strlen(var_value) - 1);
	free(var_value);
	free(var_name);
	return (new);
}

int			replace_var(char **str, char **start)
{
	char	*new;

	if (*(*str + 1) == 0)
	{
		*str = *str + 1;
		return (0);
	}
	// if ((!ft_isalpha_u(*(*str + 1)) && (*(*str + 1) != '?')))
	// {
	// 	*str = *str + 1;
	// 	return (0);
	// }
	if ((new = do_replace(start, str)) == NULL)
		return (-1);
	free(*start);
	*start = new;
	return (0);
}

void		skip_squotes(char **str)
{
	int		escape;

	escape = 0;
	(*str)++;
	while (**str != 0)
	{
		if ((**str == '\\') && (escape == 0))
			escape = 1;
		else if ((**str == '\'') && (escape == 0))
			return ;
		else if (escape == 1)
			escape = 0;
		(*str)++;
	}
}
