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
}						t_command;

typedef struct			s_globals
{
	char				**env_arr;
	int					ret;
	pid_t				pid;
}						t_globals;

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
** globals
*/

t_globals	g_globstruct;
/*
** init
*/

void    				init_globals(char *envp[]);
void    				signal_callback();
/*
** builtins
*/

int						echo(t_command *cmd);
int	   					env(t_command *cmd);
int     				sorted_env(char **env);
int	    				pwd(t_command *cmd);
int	    				cd(t_command *cmd);
int		   				export(t_command *cmd);
int	    				unset(t_command *cmd);
void	    			do_exit(t_command *cmd);

/*
** Parsing
*/

t_list_cmd				*parse(char *line);
t_list_str				*split_tokens(char *line);
t_list_str				*parse_word(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_meta(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_pipe(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_fdout(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_fdin(t_list_str *tkn, t_list_cmd **cur);
char					*solve_dollards(char *str);
int						pass_dquotes(char *s);
int						pass_squotes(char *s);
int						check_errors(char *line);

/*
** Exec
*/
void					exec_loop(char *line);
int						exec(t_list_cmd *cmds);
char					*find_bin(char *bin);
int						exec_command(t_command *cmd);
char					*find_bin_with_env(char *bin);
char					*find_bin(char *bin);
void					link_commands(t_list_cmd *l_cmd, t_list_cmd *new_cmd);
int						*open_fds_in(t_command *content);
int						solve_dquotes(char **str, char **content);
int						solve_squotes(char **str, char **content);
int						solve_escape(char **str, char **content);
int						solve_word(char **str, char **content);
char					*solve_quotings(char *content);
t_list_str				*parse_fdin(t_list_str *tkn, t_list_cmd **cur);
char					*extract_var_name(char *str);
char					*do_replace(char **start, char **str);
int						replace_var(char **str, char **start);
void					skip_squotes(char **str);
char					*solve_dollards(char *str);
void					insert_word(t_list_cmd **cur, char *word);
t_list_str				*parse_fdout(t_list_str *tkn, t_list_cmd **cur);
int						setup_pipe(t_list_cmd **cur);
int						create_piped_command(t_list_cmd **cur);
t_list_str				*parse_pipe(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_coma(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_meta(t_list_str *tkn, t_list_cmd **cur);
t_list_str				*parse_word(t_list_str *tkn, t_list_cmd **cur);
t_list_cmd				*parse_tokens(t_list_str *tokens);
void					testfree(void *param);
int						display_error(char *err);
int						is_blank(char *str);
int						is_token_error(t_list_str *tokens);
int						is_first_error(t_list_str *tokens);
int						is_syntax_error(t_list_str *tokens);
t_list_cmd				*parse(char *line);
int						check_errors(char *line);
int						err_msg(char *com, int err);
int						has_path(char *bin);
void					exec_child(t_command *cmd, char *envp[],
									char *bin, char **params);
int						exec_parent(pid_t pid, char *bin, t_command *cmd);
int						exec_command(t_command *cmd);

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
int						get_var_index(char *envp[], char *text);

/*
** Utils
*/
char					*get_var_name(char *str);
char   					**duplicate_strs(char **strs);
void    				ft_sort_string_tab(char **tab);
int     				get_strs_len(char **strs);
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

void					prompt();
void					sig_ctrlc(int signal);
void					sig_ctrlbs(int signal);
void					sig_manag(void);
int						err_msg(char *cmd, int code);


int						get_next_line(int fd, char **line);
int						find_line(t_fl *fl);
char					*ft_strnjoin(char *s1, char const *s2, size_t n);
int						init(t_fl *fl, int fd, char **line);
int						reinit(t_fl *fl);
void					ft_putstr_fd(char *s, int fd);

#endif
