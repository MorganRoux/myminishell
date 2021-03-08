/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:33:25 by mroux             #+#    #+#             */
/*   Updated: 2021/03/08 20:33:26 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstof(t_list *lst, int index)
{
	t_list	*list;
	int		i;

	i = 0;
	if (lst == 0)
		return (0);
	list = lst;
	while (list->next != 0 && i++ < index)
	{
		list = list->next;
	}
	return (list);
}
