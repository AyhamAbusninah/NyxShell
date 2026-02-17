/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:51:32 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/04 20:25:41 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"

int	is_node_empty(t_ast *node)
{
	if (!node)
		return (1);
	if (node->type == NODE_CMD)
	{
		if (!node->cmd->argv && !node->cmd->redir)
			return (1);
		return (0);
	}
	return (0);
}

t_ast	*parse_or(t_token **tok)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_and(tok);
	if (*tok && (*tok)->type == TOK_OR && is_node_empty(left))
		return (free_err_msg(left, NULL, "syntax error near `||'"));
	while (*tok && (*tok)->type == TOK_OR)
	{
		*tok = (*tok)->next;
		right = parse_and(tok);
		if (!right || is_node_empty(right))
			return (free_err_msg(left, right, "syntax error near `||'"));
		node = init_ast();
		if (!node)
			return (free_err_msg(left, right, NULL));
		node->type = NODE_OR;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}
