/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:15:00 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/09 10:20:26 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		testfree(void *param)
{
	printf("%s", (char *)param);
	getchar();
	free(param);
	printf("del");
	getchar();
}

int			display_error(char *err)
{
	ft_putstr_fd("parse error near ", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int			is_blank(char *str)
{
	return (ft_strcmp(str, " ") == 0 ||
		ft_strcmp(str, "\t") == 0);
}
