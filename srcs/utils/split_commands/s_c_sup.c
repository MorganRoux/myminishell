/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_c_sup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:33:49 by mroux             #+#    #+#             */
/*   Updated: 2021/03/08 20:33:51 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_str	*split_commandss(char *s)
{
	t_list_str	*ret;
	t_list_str	*new;
	char		*str;
	int			len;

	ret = NULL;
	while (*s != 0)
	{
		len = command_len(s);
		if (len == -1)
		{
			ft_printf("error near %c\n", *s);
			ft_lstclear(&ret, free);
			return (NULL);
		}
		str = ft_substr(s, 0, len + (*(s + len) == 0 ? 0 : 1));
		new = ft_lstnew(str);
		ft_lstadd_back(&ret, new);
		s = s + len + (*(s + len) == 0 ? 0 : 1);
	}
	return (ret);
}

char		**split_commands(char *line)
{
	t_list_str	*lst;
	char		**strs;

	lst = split_commandss(line);
	strs = list2char(lst);
	ft_lstclear(&lst, free);
	return (strs);
}
