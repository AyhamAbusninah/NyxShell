/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:18:53 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/18 01:26:33 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_cmd	t_cmd;
typedef struct s_ast	t_ast;
typedef struct s_redir	t_redir;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					visible;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_eviro
{
	char				**envb;
	t_env				*envm;
}						t_enviro;

typedef struct s_var_pipe
{
	int					pfd[2];
	int					pid_left;
	int					pid_right;
	int					status;
}						t_var_pipe;

typedef struct s_export
{
	int					i;
	int					j;
	char				**k_v;
	char				*key_to_check;
}						t_export;

/*###########################################*/
//				Expander section				//
/*###########################################*/

/* expander functions */
char					*expand_string(char *str, t_env *env, int exit_status);
void					expand_cmd_args(t_cmd *cmd, t_env *env,
							int exit_status);
void					free_expand_ast(t_ast *node, t_env *env,
							int exit_status);
void					expand_ast(t_ast *node, t_env *env, int exit_status);
void					expand_and_clean_argv(t_cmd *cmd, t_env *env, int es,
							int flag);
int						get_var_len(char *str);
int						is_valid_var_char(char c);
char					*get_env_val(char *var_name, t_env *env,
							int last_exit_status);
char					*expand_heredoc_line(char *line, t_env *env,
							int exit_status);

/* env functions */
t_env					*new_env_node(char *key, char *value);
void					add_env_var(t_env **head, char *env_str);
t_env					*init_env(char **envp);
char					*get_env_value(t_env *env, char *key);
void					free_env(t_env *env);

/* heredoc functions */
int						heredoc_handler(t_ast *node, t_env *env,
							int exit_status);
int						free_heredoc(char *line, int ret);
void					heredoc_sig(void);
void					heredoc_sig_restore(void);

/* signal functions */
void					setup_signals(void);
void					reset_signals(void);
void					signals_ignore(void);

/*###########################################*/
//				Executer section				//
/*###########################################*/

int						exec_pipe(t_ast *node, t_env *env, int es);
int						exec_cmd(t_ast *node, t_env *env, int es);
int						exec_node(t_ast *node, t_env *env, int es);
int						exec_builtin(t_ast *node, t_env *env, int es);
int						executer(t_ast *ast, t_env *env, int es);
int						is_builtin(char *arg);
char					**env_to_char(t_env *env);
char					*find_command(char *cmd, char **envp);
int						ft_perror(const char *msg, int ret);
int						apply_redirs(t_redir *r);
void					free_split(char **split_p);
void					print_error(char *cmd, char *msg);
int						check_cmd_error(char *cmd);
void					child_clean(t_ast *node, t_env *env, char **envp,
							int err);
char					**add_slash(char **envp);
int						open_redir(t_redir *r);
int						redir_fd(t_redir *r, int fd);
int						get_exit_code(int status);

int						exec_echo(t_ast *node, t_env *env);
int						exec_cd(t_ast *node, t_env *env);
int						exec_pwd(t_ast *node, t_env *env);
int						exec_unset(t_ast *node, t_env *env);
int						exec_export(t_ast *node, t_env *env_head);
int						exec_env(t_ast *node, t_env *p_env);
int						exec_exit(t_ast *node, int es);
/* ui functions */
void					print_startup_logo(void);
char					*get_prompt(t_env *env);
#endif