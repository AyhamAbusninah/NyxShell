/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:17:24 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 00:14:19 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "tokenizer.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				fd;
	int				flag;
	struct s_redir	*next;
}					t_redir;

typedef enum e_node_type
{
	NODE_OR,
	NODE_AND,
	NODE_PIPE,
	NODE_CMD
}					t_node_type;

typedef struct s_cmd
{
	char			**argv;
	int				*flags;
	t_redir			*redir;
}					t_cmd;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd			*cmd;
}					t_ast;

typedef struct s_add_argv
{
	char			**new_arr;
	int				*new_flags;
	int				i;
	int				len;
	int				j;
}					t_add_argv;

/* parser functions */
t_ast				*parse_or(t_token **tok);
t_ast				*parse_and(t_token **tok);
t_ast				*parse_pipe(t_token **tok);
t_ast				*parse_cmd(t_token **tok);
t_ast				*parser(t_token *tok);

/* utils */
t_redir_type		get_redir_from_tok(t_token_type type);
int					get_redir_type(char **s);
int					is_node_empty(t_ast *node);
int					is_redir(t_token_type type);

/* initialize */
t_ast				*init_ast(void);
t_cmd				*init_cmd(void);

/* error and clean handle */
int					error_msg(char *msg);
t_ast				*free_err_msg(t_ast *left, t_ast *right, char *msg);
void				free_redirs(t_redir *r);
void				free_ast(t_ast *ast);

#endif