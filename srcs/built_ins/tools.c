/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:22:41 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/05 10:02:57 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_itsokay(int c)
{
	if ((ft_isdigit(c) || ft_isalpha(c))
		|| (c == '-' || c == '_' || c == ':' || c == '/'))
		return (0);
	return (1);
}
