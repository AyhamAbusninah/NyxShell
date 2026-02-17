/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:09:59 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/14 19:40:11 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/tokenizer.h"

void	increaser(t_var *var)
{
	if (var->type == TOK_OR || var->type == TOK_AND
		|| var->type == TOK_REDIR_APPEND || var->type == TOK_HEREDOC)
		var->i++;
}

static t_token	*handle_word_token(char *line, t_var *var)
{
	var->value = split_word(line, var);
	if (!var->value)
	{
		var->final_lst = free_all(var->final_lst, NULL);
		return (NULL);
	}
	var->node = m_lstnew(var->type, var->value, var->flag);
	if (!var->node)
	{
		var->final_lst = free_all(var->final_lst, var->value);
		return (NULL);
	}
	m_lstadd_back(&var->final_lst, var->node);
	return (var->final_lst);
}

static t_token	*handle_other_token(t_var *var)
{
	var->value = NULL;
	var->node = m_lstnew(var->type, var->value, var->flag);
	if (!var->node)
	{
		var->final_lst = free_all(var->final_lst, var->value);
		return (NULL);
	}
	m_lstadd_back(&var->final_lst, var->node);
	var->i++;
	return (var->final_lst);
}

static t_token	*process_token(char *line, t_var *var)
{
	var->type = type_checker(line, *var);
	if (!var->type)
		return (NULL);
	increaser(var);
	if (var->type == TOK_WORD)
		return (handle_word_token(line, var));
	return (handle_other_token(var));
}

t_token	*tokenizer(char *line)
{
	t_var	var;

	if (!line)
		return (NULL);
	token_prepare(&var);
	while (line[var.i] != '\0')
	{
		while (is_space(line[var.i]))
			var.i++;
		if (line[var.i] == '\0')
			break ;
		if (!process_token(line, &var))
			return (free_all(var.final_lst, NULL));
	}
	return (var.final_lst);
}
