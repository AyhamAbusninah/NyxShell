/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:20:59 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 23:34:11 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define NEGATIVE_DOLLAR 1

# include "minishell.h"

typedef enum e_token_type
{
	TOK_OR = 1,
	TOK_AND,
	TOK_PIPE,
	TOK_WORD,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_OBRACKET,
	TOK_CBRACKET
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			**value;
	struct s_token	*next;
	struct s_token	*prev;
	int				flag;
}					t_token;

typedef struct s_var
{
	size_t			i;
	t_token			*final_lst;
	char			**value;
	t_token_type	type;
	t_token			*node;
	int				flag;
}					t_var;

typedef struct s_build_word_var
{
	char			*w;
	size_t			w_len;
	size_t			j;
	char			qoute;
}					t_build_word_var;

t_token				*m_lstnew(t_token_type type, void *value, int flag);
void				m_lstadd_back(t_token **lst, t_token *new);
t_token				*m_lstlast(t_token *lst);
void				m_lstclear(t_token **lst, void (*del)(void *));
void				m_lstdelone(t_token *lst, void (*del)(void *));
t_token				*tokenizer(char *line);
t_token				*free_all(t_token *lst, char **value);
void				token_prepare(t_var *var);
t_token_type		type_checker(char *str, t_var var);
char				**split_word(char *str, t_var *var);
int					is_space(char c);
int					is_sep(char c);
char				*free_split_word(char **arr, size_t n, int error);
void				free_split_void(void *p);

#endif
