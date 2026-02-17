/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:11:06 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/07 20:40:25 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"

t_ast	*init_ast(void)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(*ast));
	if (!ast)
		return (NULL);
	ast->left = NULL;
	ast->right = NULL;
	ast->cmd = NULL;
	return (ast);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->flags = NULL;
	cmd->redir = NULL;
	return (cmd);
}

t_redir_type	get_redir_from_tok(t_token_type type)
{
	if (type == TOK_REDIR_IN)
		return (REDIR_IN);
	else if (type == TOK_REDIR_OUT)
		return (REDIR_OUT);
	else if (type == TOK_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_APPEND);
}
