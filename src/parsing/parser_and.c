/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:09:57 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/04 20:13:37 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"

t_ast	*parse_and(t_token **tok)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_pipe(tok);
	if (*tok && (*tok)->type == TOK_AND && is_node_empty(left))
		return (free_err_msg(left, NULL, "syntax error near `&&'"));
	while (*tok && (*tok)->type == TOK_AND)
	{
		*tok = (*tok)->next;
		right = parse_pipe(tok);
		if (!right || is_node_empty(right))
			return (free_err_msg(left, right, "syntax error near `&&'"));
		node = init_ast();
		if (!node)
			return (free_err_msg(left, right, NULL));
		node->type = NODE_AND;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}
