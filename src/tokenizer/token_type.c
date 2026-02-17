/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:06:04 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/04 00:16:10 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/tokenizer.h"

t_token_type	type_checker(char *line, t_var var)
{
	if (line[var.i] == '|' && line[var.i + 1] == '|')
		return (TOK_OR);
	else if (line[var.i] == '&' && line[var.i + 1] == '&')
		return (TOK_AND);
	else if (line[var.i] == '>' && line[var.i + 1] == '>')
		return (TOK_REDIR_APPEND);
	else if (line[var.i] == '<' && line[var.i + 1] == '<')
		return (TOK_HEREDOC);
	else if (line[var.i] == '<')
		return (TOK_REDIR_IN);
	else if (line[var.i] == '>')
		return (TOK_REDIR_OUT);
	else if (line[var.i] == '(')
		return (TOK_OBRACKET);
	else if (line[var.i] == ')')
		return (TOK_CBRACKET);
	else if (line[var.i] == '|')
		return (TOK_PIPE);
	else if (line[var.i] == '&')
		return (0);
	else
		return (TOK_WORD);
}
