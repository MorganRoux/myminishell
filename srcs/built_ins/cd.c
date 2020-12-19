/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:01:03 by alkanaev          #+#    #+#             */
/*   Updated: 2020/12/19 10:48:37 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	dirnow_update(t_command *mimi, char *dir_now) //update dir_now in the structure
{
	if (mimi->dir_now)
		free(mimi->dir_now);
	mimi->dir_now = ft_strdup(dir_now);
}

char		*parh_checker(t_command *mimi, char *cmd)
{
	if (!cmd)
		return (var_checker(mimi, mimi->env_arr, "HOME")); //if no name of folder given - go to home dir
	else
		return (cmd);
}

void		cd_err_case(t_command *mimi, char *str, int err_code)
{
	if (err_code == 1)
		ft_putstr_fd("MINISHELL: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	mimi->ret = 1;
}

void    com_cd(t_command *mimi, char **cmd)
{
	char	*dir_now; //current working dir
	int		argc; //ammount of cmds

	//ft_putstr2(cmd);
	dir_now = NULL;
	argc = cnt_com_parts(cmd); //cnt ammount
	mimi->ret = 0; 
    //chdir() изменяет текущий каталог каталог на path. Если он не смог перейти по path,
    //то возвращает -1 (пригодится для проверки path на валидность)
    if (argc > 2)
	{
		cd_err_case(mimi, "Too much arguments", 1);
		return ;
	}
	if (chdir(get_path_cd(mimi, cmd[1])) < 0) //change dir to written name of folder
			cd_err_case(mimi, strerror(errno), 1);
    //getcwd копирует абсолютный путь к текущему рабочему каталогу в массиве,
    //на который указывает buf, имеющий длину size. Если подавать NULL, 
    //то getcwd сама аллокирует память, size в этом случае игнорируется
	if (!(dir_now = getcwd(NULL, 0))) //
	{
		cd_err_case(mimi, "error retrieving current directory: getcwd: "
		"cannot access parent directories: No such file or directory", 2); //internal shell text error
		envvar_update(mimi, ft_strjoin(mimi->env_arr[ind_of_envvar(mimi, "PWD")], "/."));
		dirnow_update(mimi, var_checker(mimi, mimi->env_arr, "PWD"));
		return ;
	}
    //update variables from env // if it's ok - write new path to PWD var inside mimi -> env
	envvar_update(mimi, ft_strjoin("PWD=", dir_now));
    //if it's ok - write new path to PWD var inside mimi -> curr_dir
	dirnow_update(mimi, var_checker(mimi, mimi->env_arr, "PWD")); 
	strdel(&dir_now);
}
