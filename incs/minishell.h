/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:35:37 by mroux             #+#    #+#             */
/*   Updated: 2020/12/19 16:12:13 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libftprintf.h"
# include "get_next_line.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>

typedef t_list          t_list_str;         // t_list with content pointing to a (char *)
typedef t_list          t_list_cmd;         // t_list with content pointing to a (t_command *)


/**
 * PIPES lOGIC
 *             _________________
 * STDOUT  --> _____flux_out____ -> fd_out, next command(pipe_in)
 *                                    ______________________
 * prev command (pipe_out), fd_in ->  _________flux_in______ -> STDIN           
 * 
 * */
typedef struct	        s_command           // This describes ONE command
{
	char		        *exec;              // name of the command
	t_list_str		    *args;              // arguments (without redirections)
	t_list_str	        *files_in;          // files to redirect towards stdin
	t_list_str		    *files_out;         // files to redirect from stdout
    int                 *fd_in;             // fd of all the files_in
    int                 *fd_out;            // fd of all the files_out
    int                 *pipe;
    int                 flux_in[2];          
    int                 flux_out[2];
    struct s_command    *prev;              // !=NULL if pipe from  <-
    int                 status;

	char				**env_arr;          // env
	int					ret;                // echo $? - return value of previous command
	char				*given;             // given input
	char				**sep_cmds;         // commands to split the input on ;
	int					check_pipe;         // pipe + -
	//int					pipe[2]; // 1 - to write to / 2 - to read from
	int					bad_pipe;           // check if pipe is only one separated symbol
	char				*dir_now;           // dir where we are now
	char				*input;             // command
}				        t_command;


// Parsing
t_list_cmd              *parse();
t_list_str              *split_tokens(char *line);
t_list_str              *parse_word(t_list_str *tkn, t_list_cmd **cur);
t_list_str              *parse_meta(t_list_str *tkn, t_list_cmd **cur);
t_list_str              *parse_pipe(t_list_str *tkn, t_list_cmd **cur);
t_list_str              *parse_fdout(t_list_str *tkn, t_list_cmd **cur);
t_list_str              *parse_fdin(t_list_str *tkn, t_list_cmd **cur);

// Exec
void                    exec(t_command *mimi, t_list_cmd  *cmds, char *envp[]);
char                    *find_bin(char *bin, char *envp[]);
int                     exec_command(t_command *cmd, char *envp[]);

// Redirection
int                     *open_fds(t_list_str *files, int  flag);
int                     open_redirections(t_list_cmd *cmd);
int                     close_fds(int *fds, int size);
int                     close_redirections(t_list_cmd *cmd);
int                     apply_redirections(t_command *cmd);
int                     apply_redirections_in(t_command *cmd);
int                     apply_redirections_out(t_command *cmd);
int                     is_redirection_in(t_command *cmd);
int                     is_redirection_out(t_command *cmd);
int                     number_of_redirection_in(t_command *cmd);
int                     number_of_redirection_out(t_command *cmd);

//Piping
int                     open_pipe(t_list_cmd *cmd);
int                     close_pipe(t_list_cmd *cmd);
int                     apply_pipes(t_command *cmd);
int                     apply_pipe_in(t_command *cmd);
int                     apply_pipe_out(t_command *cmd);
int                     is_pipe_in(t_command *cmd);
int                     is_pipe_out(t_command *cmd);

//Env
char                    *get_var(char *envp[], char *var);

//Utils
void                    print_strs(char **strs);
void                    print_lst_str(t_list_str *strs);
void                    print_cmd(t_command *cmd);
void                    print_cmds(t_list_cmd *cmd);
int                     is_meta_char(char c);
int                     is_meta_str(char *str);
int                     is_space_str(char *str);
char                    **list2char(t_list_cmd *cmds);
char                    **extract_command_and_args(t_command *cmd);
void                    free_strs(char **strs);
char                    **get_paths(char  *envp[]);

//List
t_list_cmd              *ft_lstinit();
t_list                  *ft_lstof(t_list *lst, int index);

//buit-ins and stuff around
void	dirnow_update(t_command *mimi, char *dir_now);
char		*parh_checker(t_command *mimi, char *cmd);
void		cd_err_case(t_command *mimi, char *str, int err_code);
void    com_cd(t_command *mimi, char **cmd);
int         cnt_com_parts(char **str);
int         check_nl(char *cmds);
void		com_echo(t_command *mimi, char **cmds);
void	arr_cleaner(char **str);
int			ind_of_envvar(t_command *mimi, char *var);
void		del_envvar(t_command *mimi, char *var);
void		envvar_update(t_command *mimi, char *var);
void		envvar_sort(char **env_arr, int len);
void		envvar_print(char *env_arr);
void		envvar_pr_sort(t_command *mimi);
void	strdel(char **s);
void		com_env(t_command *mimi);
int     exec_built_ins(t_command *mimi, char **cmd);
int		arg_checker(char *str);
void	exit_stat(t_command *mini, char *str);
void	com_exit(t_command *mini, char **args);
int		space_checker(char *str);
int		env_valid(char *env_arr);
void		upd_newenv(t_command *mimi, char *env_update);
int		exp_err_case(t_command *mimi, char *cmd);
int		val_adder(char *var);
void			com_export(t_command *mimi, char **cmd);
int	get_char_pos(char *str, char c);
char	*var_checker(t_command *mini, char **env_arr, char *var);
void	com_pwd(t_command *mimi);
int		check_pres(char ch, char *str);
int		wrd_cnt(char *str, char *charset);
char	*cutter(char *str, char *charset, int *i);
char	**split_mod(char *str, char *charset);
char		*join_mod(char const *s1, const char *s2, char const *s3);
int		env_checker(t_command *mimi, char *var);
int     undet_err_case(t_command *mimi, char *cmd);
void    com_unset(t_command *mimi, char **cmd);




#endif
