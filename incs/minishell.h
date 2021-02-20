/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:35:37 by mroux             #+#    #+#             */
/*   Updated: 2021/02/09 13:17:42 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libftprintf.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <signal.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/*
** t_list_str - t_list with content pointing to a (char *)
** t_list_cmd - t_list with content pointing to a (t_command *)
*/

typedef t_list			t_list_str;
typedef t_list			t_list_cmd;

/*
** PIPES lOGIC
**             _________________
** STDOUT  --> _____flux_out____ -> fd_out, next command(pipe_in)
**                                    ______________________
** prev command (pipe_out), fd_in ->  _________flux_in______ -> STDIN
*/

/*
** exec - name of the command
** args - arguments (without redirections)
** files_in - files to redirect towards stdin
** files_out - files to redirect from stdout
** fd_in - fd of all the files_in
** fd_out - fd of all the files_out
** prev - !=NULL if pipe from  <-
** env_arr - env
** ret - echo $? - return value of previous command
** check_pipe - pipe + -
** bad_pipe - check if pipe is only one separated symbol
** dir_now - dir where we are now
*/

typedef struct			s_command
{
	char				*exec;
	t_list_str			*args;
	t_list_str			*files_in;
	t_list_str			*files_out;
	t_list_str			*files_append;
	int					*fd_in;
	int					*fd_out;
	int					*pipe;
	int					flux_in[2];
	int					flux_out[2];
	struct s_command	*prev;
	int					status;
	char				**env_arr;
	int					ret;
	int					check_pipe;
	int					bad_pipe;
	char				*dir_now;
	pid_t				pid;
	int					ch;
}						t_command;

/*
** gnl
*/

typedef struct			s_fl
{
	char				*buffer;
	int					pos;
	int					bytes_read;
	int					fd;
}						t_fl;

/*
** builtins
*/

void					echo(t_command *global_command, t_command *cmd);
void   					env(t_command *global_command, t_command *cmd);
void    				pwd(t_command *global_command, t_command *cmd);
void    				cd(t_command *global_command, t_command *cmd);
void    				do_exit(t_command *global_command, t_command *cmd);
/*
** Parsing
*/

t_list_cmd				*parse(char *line, t_command *global_command);
t_list_str				*split_tokens(char *line);
t_list_str				*parse_word(t_list_str *tkn, t_list_cmd **cur,
									t_command *global_command);
t_list_str				*parse_meta(t_list_str *tkn, t_list_cmd **cur,
									t_command *global_command);
t_list_str				*parse_pipe(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_fdout(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_fdin(t_list_str *tkn, t_list_cmd **cur);
char					*solve_dollards(char *str, t_command *global_command);
int						pass_dquotes(char *s);
int						pass_squotes(char *s);
int						check_errors(char *line, t_command *global_command);

/*
** Exec
*/
void					exec_loop(char *line, t_command *g_globstruct);
int						exec(t_command *mimi, t_list_cmd *cmds);
char					*find_bin(char *bin, t_command *global_command);
int						exec_command(t_command *cmd, t_command *global);
char					*find_bin_with_env(char *bin, t_command *gc);
char					*find_bin(char *bin, t_command *global_command);
void					link_commands(t_list_cmd *l_cmd, t_list_cmd *new_cmd);
int						*open_fds_in(t_command *content);
int						solve_dquotes(char **str, char **content);
int						solve_squotes(char **str, char **content);
int						solve_escape(char **str, char **content);
int						solve_word(char **str, char **content);
char					*solve_quotings(char *content);
t_list_str				*parse_fdin(t_list_str *tkn, t_list_cmd **cur);
char					*extract_var_name(char *str);
char					*do_replace(char **start, char **str, t_command *gc);
int						replace_var(char **str, char **start, t_command *gc);
void					skip_squotes(char **str);
char					*solve_dollards(char *str, t_command *global_command);
void					insert_word(t_list_cmd **cur, char *word,
									t_command *gc);
t_list_str				*parse_fdout(t_list_str *tkn, t_list_cmd **cur);
int						setup_pipe(t_list_cmd **cur);
int						create_piped_command(t_list_cmd **cur);
t_list_str				*parse_pipe(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_coma(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_meta(t_list_str *tkn, t_list_cmd **cur,
									t_command *gc);
t_list_str				*parse_word(t_list_str *tkn, t_list_cmd **cur,
									t_command *gc);
t_list_cmd				*parse_tokens(t_list_str *tokens,
									t_command *global_command);
void					testfree(void *param);
int						display_error(char *err);
int						is_blank(char *str);
int						is_token_error(t_list_str *tokens);
int						is_first_error(t_list_str *tokens);
int						is_syntax_error(t_list_str *tokens);
t_list_cmd				*parse(char *line, t_command *global_command);
int						check_errors(char *line, t_command *global_command);
int						err_msg(char *com, int err);
int						has_path(char *bin);
void					exec_child(t_command *cmd, char *envp[],
									char *bin, char **params);
int						exec_parent(pid_t pid, char *bin, t_command *cmd);
int						exec_command(t_command *cmd, t_command *global_command);

/*
** Redirection
*/

int						*open_fds(t_list_str *files, int flag);
int						open_redirections(t_list_cmd *cmd);
int						close_fds(int *fds, int size);
int						close_redirections(t_list_cmd *cmd);
int						apply_redirections(t_command *cmd);
int						apply_redirections_in(t_command *cmd);
int						apply_redirections_out(t_command *cmd);
int						is_redirection_in(t_command *cmd);
int						is_redirection_out(t_command *cmd);
int						number_of_redirection_in(t_command *cmd);
int						number_of_redirection_out(t_command *cmd);

/*
** Piping
*/

int						open_pipe(t_list_cmd *cmd);
int						close_pipe(t_list_cmd *cmd);
int						apply_pipes(t_command *cmd);
int						apply_pipe_in(t_command *cmd);
int						apply_pipe_out(t_command *cmd);
int						is_pipe_in(t_command *cmd);
int						is_pipe_out(t_command *cmd);

/*
** Env
*/

char					*get_var(char *envp[], char *var);

/*
** Utils
*/
int     				ft_isalpha_u(char c);
int     				ft_isalnum_u(char c);
void					print_strs(char **strs);
void					print_lst_str(t_list_str *strs);
void					print_cmd(t_command *cmd);
void					print_cmds(t_list_cmd *cmd);
int						is_meta_char(char c);
int						is_meta_str(char *str);
int						is_space_str(char *str);
char					**list2char(t_list_cmd *cmds);
char					**extract_command_and_args(t_command *cmd);
void					free_strs(char **strs);
void					free_cmds(t_list_cmd *cmds);
void					free_cmd(void *param);
char					**get_paths(char *envp[]);
char					**split_commands(char *line);
int						is_sep(char c);
char					**ftt_split(char const *s);
int						command_len(char *s);
t_list_str				*split_commandss(char *s);
char					**split_commands(char *line);

/*
** List
*/
t_list_cmd				*ft_lstinit();
t_list					*ft_lstof(t_list *lst, int index);

/*
** buit-ins, signals and stuff around
*/

void					upd_newenv2(t_command *mimi, char *env_upd);
void					upd_newenv2_sup(t_command *mimi, char **tmp, int j);
void					c_exp_sup(t_command *mimi, char **cmd, int k, int len);
int						ft_itsokay(int c);
int						c_exp_sup2(t_command *mimi, char **cmd, int k);
void					c_exp_sup3(t_command *mimi, char **cmd, int *k,
								int *len);

void					dirnow_update(t_command *mimi, char *dir_now);
char					*parh_checker(t_command *mimi, char *cmd);
void					cd_err_case(t_command *mimi, char *str, int err_code);
void					com_cd(t_command *mimi, char **cmd);
int						cnt_com_parts(char **str);
int						check_nl(char *cmds);
void					com_echo_sup(int k, int i, int argc, char **cmds);
//void					com_echo(t_command *mimi, char **cmds);
void					arr_cleaner(char **str);
int						ind_of_envvar(t_command *mimi, char *var);
void					del_envvar(t_command *mimi, char *var);
void					envvar_update(t_command *mimi, char *var);
void					envvar_sort(char **env_arr, int len);
void					envvar_print(char *env_arr);
void					envvar_pr_sort(t_command *mimi);
void					strdel(char **s);
void					env_filling(char **envp, t_command *g_globstruct);
//void					com_env(t_command *mimi);
// int						exec_built_ins(t_command *mimi, char **cmd,
// 									t_command *cur_cmd);
int						arg_checker(char *str);
void					com_exit_sup(t_command *mimi, char *str);
void					com_exit(t_command *mimi, char **args);
int						space_checker(char *str);
int						env_valid(char *env_arr);
void					upd_newenv(t_command *mimi, char *env_update);
int						exp_err_case(t_command *mimi, char *cmd);
int						val_adder(char *var);
void					com_export(t_command *mimi, char **cmd);
int						get_char_pos(char *str, char c);
char					*var_checker(t_command *mimi, char **env_arr,
									char *var);
void					com_pwd(t_command *mimi);
int						check_pres(char ch, char *str);
int						wrd_cnt(char *str, char *charset);
char					*cutter(char *str, char *charset, int *i);
char					**split_mod(char *str, char *charset);
char					*join_mod(char const *s1, const char *s2,
									char const *s3);
int						env_checker(t_command *mimi, char *var);
int						undet_err_case(t_command *mimi, char *cmd);
void					com_unset_sup(int i, int argc, t_command *mimi,
									char **cmd);
void					com_unset(t_command *mimi, char **cmd);
void					close_mimi(t_command *mimi, int ret);

void					upd_cwd(t_command *mimi, char *cwd);
void					prompt(t_command *mimi);
void					sig_ctrlc(int signal);
void					sig_ctrlbs(int signal);
void					sig_manag(void);
int						err_msg(char *cmd, int code);

/*
** gnl - я понятия не имею что именно я сделала, но без gnl в mimishell.h
** оно перестало работать... Нет времени разбираться.
*/

int						get_next_line(int fd, char **line, t_command *mimi);
int						find_line(t_fl *fl);
char					*ft_strnjoin(char *s1, char const *s2, size_t n);
int						init(t_fl *fl, int fd, char **line);
int						reinit(t_fl *fl);
void					ft_putstr_fd(char *s, int fd);

#endif
