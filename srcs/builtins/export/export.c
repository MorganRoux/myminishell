/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:26:41 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:30:49 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_export_arg(char *str)
{
	char	*var_name;
	int		i;

	i = 0;
	if (str == NULL)
		return (1);
	var_name = get_var_name(str);
	if (var_name == NULL)
		return (0);
	if (ft_isdigit(var_name[0]))
	{
		free(var_name);
		return (0);
	}
	while (var_name[i] != 0)
	{
		if (!ft_isalnum_u(var_name[i++]))
		{
			free(var_name);
			return (0);
		}
	}
	free(var_name);
	return (1);
}

int		check_export_args(t_list_str *args)
{
	(void)args;
	while (args != NULL)
	{
		if (!check_export_arg(args->content))
		{
			ft_printf("export: %s : identifiant non valable\n", args->content);
			return (0);
		}
		args = args->next;
	}
	return (1);
}

int		find_equal(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != 0)
	{
		if (*str++ == '=')
			return (1);
	}
	return (0);
}

int		export(t_command *cmd)
{
	t_list_str	*args;

	if ((args = cmd->args) == NULL)
		return (sorted_env(g_globstruct.env_arr));
	if (!check_export_args(args))
		return (1);
	while (args != NULL)
	{
		if (find_equal(args->content))
		{
			g_globstruct.env_arr = delete_from_env(
				g_globstruct.env_arr, args->content);
			g_globstruct.env_arr = add_to_env(
				g_globstruct.env_arr, args->content);
		}
		args = args->next;
	}
	return (0);
}
