/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 04:52:38 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 22:41:46 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define SIMPLE_QUOTE "'"
# define DOUBLE_QUOTE "\""
# define PIPE_TOKEN "|"
# define DOLLAR "$"
# define DOLLAR_QUESTION "$?"
# define REDIR_LEFT "<"
# define REDIR_RIGHT ">"
# define REDIR_DOUBLE_LEFT "<<"
# define REDIR_DOUBLE_RIGHT ">>"

typedef enum e_state
{
	base,
	s_quote,
	d_quote,
	single_in_double,
	double_in_single
}					t_state;

enum
{
	simple_quote,
	double_quote,
	pipe_token,
	dollar,
	dollar_question,
	redir_none,
	redir_left,
	redir_right,
	redir_double_left,
	redir_double_right,
	echo_enum,
	cd_enum,
	pwd_enum,
	export_enum,
	unset_enum,
	env_enum,
	exit_enum,
	not_builtin
};

typedef struct s_cmd
{
	char			**cmd;
	int				*to_expand;
	int				*var_len;
	char			*path;
	char			**input_file;
	char			**output_file;
	int				*hd;
	char			**token;
	int				redir;
	int				*redir_type;
	int				redir_in;
	int				redir_out;
	int				p;
}					t_cmd;

typedef struct s_mini
{
	t_cmd			*cmds;
	char			**envp;
	int				nb_cmd;
	int				act_fd;
}					t_mini;

typedef struct s_files
{
	int				position_infile;
	int				position_outfile;
	int				fd_infile;
	int				fd_outfile;
	int				i;
	int				**fd_pipe;
	int				opt_exit;
	int				opt_stdout;
}					t_files;

// typedef struct s_glob
// {
// 	int		g_status;
// 	t_mini	*minsh;
// 	char	*line;
// }	t_glob;

/* Env & env update */

int					ft_env_size(char **envp);
char				**ft_realloc_env(char **envp);
char				*ft_get_var(char **env, char *var);
void				ft_clean_env(char **env);
int					ft_update_pwd(char **env, char *oldpwd, char *pwd);

/* Split utils */

void				ft_clean_split(char **split);
int					ft_split_len(char **split);

/* Check tokens utils */

int					ft_dollar(char *line, int i, t_cmd *cmd);
int					ft_redir(char *line, int i, t_cmd *cmd);
int					ft_pipe(char *line, int i, t_cmd *cmd);
int					ft_quote(char *line, int i, t_cmd *cmd);

/* Check tokens main */

void				ft_check_elements(char *line, t_cmd *cmd);
int					ft_is_token(char c);

/* Cmd trim */

char				**ft_cmd_split(char const *s, char *set);

/* Search redir */

int					ft_alloc_files(t_cmd *cmd);
int					ft_fnm_len(char *line, int i, t_cmd *cmd);
char				*ft_search_redir(char *str, t_cmd *cmd);

/* Utils redir */

int					ft_next_redir(char *str, int i);
void				ft_pass_space(char *str, int *i, int *n);
int					ft_check_parse_redir(char *str, int i);
char				*ft_tjoin(char *s1, char *s2);

/* Check quotes */

int					ft_check_quote_syntax(char *str);
int					ft_check_cmd(char **cmd);

/* Quote state */

t_state				ft_get_state(char *s, int i);

/* Quote state utils */

t_state				ft_process_base(char c, t_state state);
t_state				ft_process_single_quote(char c, t_state state);
t_state				ft_process_double_quote(char c, t_state state);
t_state				ft_process_single_in_double(char c, t_state state);
t_state				ft_process_double_in_single(char c, t_state state);

/* Dollar */

char				*ft_dol_search(char *arg, char **env, t_cmd *cmd, int *j);

/* Checking */

char				ft_check_dt(char *str);
int					ft_check_pipes(char *str);
int					ft_wf(char **input, char **output, int *redir_type);
char				ft_check_triple_redir(char *str);
int					ft_check_dir(t_mini *mini, int pos);

/* Free */

void				ft_free_cmds(int i, t_mini *mini);

/* Remove Quotes */

void				ft_replace_quotes(t_cmd *cmd, int len);
char				*ft_wo_quote(char *str);

/* Check Prompt */

int					ft_check_prompt(char *line);
int					ft_triple(char *line);
int					ft_check_redir(t_mini *mini, int j);

/* Get */

void				ft_search_path(t_mini *mini, int n);

/* Line */

int					ft_cmds(char **cmd, t_cmd *cmds, char **env);
int					ft_line(char *line, t_mini *mini);

/* Expand */

void				ft_to_expand(char *arg, t_cmd *cmd);
int					ft_is_expandable(char *arg, int i);

// ------------------------------------------------------------------
char				**environment(char **envp);
int					ft_strlen_double_tab(char **str);
void				error_exit(void);
int					find_last_char(char *str, char c);
char				*ft_join_triple(char *s1, char *s2, char *s3);
int					check_char(char *str, char c);
void				clear_double_tab(char **tabolf);
void				ctrlc(int signal);

// ------------------------------------------------------------------

/* Envrionement */

int					ft_env_size(char **envp);
char				**ft_realloc_env(char **envp);
char				*ft_get_var(char **env, char *var);
void				ft_clean_env(char **env);
int					ft_update_env(char **env, char *oldpwd, char *pwd);

//-----------------------execution---------------------------------

// dossier pipe_fd
// int **pipe_fd(int nb_pipe);
// void close_pipe(int **fd_tab, int size);
void				clear_double_tab_int(int **fd_tab, int size);

// dossier exec
void				exec(t_mini *minsh);
void				pipex(t_mini *minsh, int *pid);
void				ft_pipex_error(int **pfd, t_mini *minsh);
void				child(t_mini *minsh, int **fd_pipe, int position);

//-----> a verifier les infiles et outfiles

// si cmd il y a:
int					check_builtin(char **cmd);
void				cmds(t_mini *minsh, int position);
void				copy_cmd(char *temp_cmd, int *pos, t_cmd *macmd);
void				err_file_not_found(t_mini *minsh, t_cmd *macmd, int err);
void				err_cmd_not_found(t_mini *minsh, t_cmd *macmd);
void				exit_in_child(t_mini *minsh, int position);
void				cmd_no_path(t_cmd *macmd, t_mini *minsh);
void				cmd_with_path(t_cmd *macmd, t_mini *minsh);

// builtin
int					b_cd(t_mini *minsh, int position);
void				ft_free_one(char *sfree, char *sjoin, t_mini *minsh);
int					check_in_env(char *str, int len, t_mini *minsh);
int					check_for_create_env(t_mini *minsh);
void				update_pwd_both(t_mini *minsh, char *s_new, char *s_old);
void				update_or_create_env(t_mini *minsh, char *s_new,
						char *s_old);
int					change_dir(t_mini *minsh, int position, int size);
int					size_double_tab(char **tab_char);
void				pwd(t_mini *minsh, int position);
void				b_echo(t_mini *minsh, int position);
int					b_env(t_mini *minsh, int position);
void				free_double_tab_char(char **str);
int					b_unset(t_mini *minsh, int position);
void				free_double_tab_char_export(char **str, int j);

// for exit
int					check_number(char *str);

// un dossier complet pour export
int					b_export(t_mini *minsh, int position);
void				swap(char **first, char **second);
void				change_null_to_equal(char **envp);
int					find_to_del(char **envp);
char				**del_one(char **envp, int position);
int					var_in_env_with_plus(t_mini *minsh, int pos, int p_arg,
						int pos_equal);
int					var_in_env_no_plus(t_mini *minsh, int pos, int p_arg,
						int pos_equal);
char				**create_new_env_no_plus(t_mini *minsh, int s_env, int pos,
						int p_arg);
char				*secur_alloc_supp_plus(char *begin);
void				normi_supp_plus_2(char *str, char *begin, char *end,
						int pos_equal);
char				*normi_supp_plus(char *begin, char *end, int pos_equal,
						int len);
void				security_malloc_for_new_env(t_mini *minsh, char **new_env,
						int i);
void				change_equal_to_null(char **envp);
int					find_char(char *str, char c);
int					is_valid_variable(char *str, int equal_position);
int					upd_env(t_mini *minsh, int position, int position_arg,
						int pos_equal);
char				*join_for_plus(char *envp_to_change, char *str_to_join,
						int pos_equal);
char				*supp_plus(char *str, int pos_equal);
void				upd_env_plus(t_mini *minsh, int position, int position_arg,
						int pos_equal);
void				print_alpha_env(t_mini *minsh, int position, char **envp);
int					put_in_exp(t_mini *minsh, int pos, int i);
char				*ft_strdup_with_two_null(char *src);
char				**dup_env_for_all(t_mini *minsh, char **envp);
void				change_equ_to_null_for_exp(char **temp_envp);

// no fork
void				no_fork(t_mini *minish);
void				exit_not_in_fork(t_mini *minsh);

// files
int					files(t_mini *minsh, int **fd_pipe, int position,
						int opt_exit);
int					err_bis(t_mini *minsh, t_files *s_f, int position);
int					ft_redir_double_right(t_mini *minsh, int position,
						t_files *s_f);
int					ft_redir_right(t_mini *minsh, int position, t_files *s_f);
int					ft_redir_double_left(t_mini *minsh, int position,
						t_files *s_f);
int					ft_redir_left(t_mini *minsh, int position, t_files *s_f);
int					ft_dup_fd(t_mini *minsh, int position, t_files *s_f);
void				initialise_struct(t_files *s_f, int **fd_pipe,
						int opt_exit);

// infile et oufile
// int *nb_inf_out(t_cmd *cmd);
// void infiles(t_mini *minsh, int **fd_pipe, int position, int *inf_out);
// void outfiles(t_mini *minsh, int **fd_pipe, int position, int *inf_out);
void				here_doc(t_cmd *cmd, int *pos, t_mini *minsh);
char				*ft_dol_search_bis(char *arg, char **env);
void				create_temp_files(t_mini *minsh);
void				send_act_cmd_for_unlink(t_mini *minsh);

// free
void				free_t_mini(t_mini *minsh);
void				free_t_cmd(t_cmd *macmd);
void				free_t_mini_export(t_mini *minsh, int size_env);

// print error
void				print_error(char *str);
char				*ft_strjoin_triple(char *str1, char *str2, char *str3);
void				secure_printf(t_mini *minsh, int position, char *str,
						int nl);

void				handle_ctrlc(int signal);
void				ctrl_backslash(int signal);

char				*create_rand_name_bis(int *pos);
char				*create_rand_name_with_int(int *pos);
void				create_str_and_numb(t_mini *minsh, int *pos, char **str,
						char **numb);
char				*create_random_name(t_mini *minsh, int *pos);
int					ft_line_empty(char *line, int todo);
char				*read_next_line(int fd);

// ctrl c
t_mini				*stat_pointer(t_mini *minsh);
void				ctrl_c_here_doc(int signal);
char				*stat_pointer_char(char *str);

void				create_file_for_dad(t_mini *minsh);

// export patch
int					check_existence(t_mini *minsh, char *str);
int					export_no_equal(t_mini *minsh, int position, int i);
int					print_not_valid_identifier(t_mini *minsh, int pos, int i);
unsigned long long	ft_atoi_long_long(char *str);
void				print_and_free(t_mini *minsh, int position, \
char **temp_envp);
void				sort_envp(char **envp);
char				*put_quotes_in_string(char *str, int equ);
int					fork_or_not(t_mini *minsh);
void				ft_start_main(int argc, char **argv, \
char **envp, t_mini *mini);
int					ft_line_empty(char *line, int todo);

#endif
