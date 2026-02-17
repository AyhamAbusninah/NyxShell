/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:17:34 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/16 20:42:13 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

int	exec_node(t_ast *node, t_env *env, int es)
{
	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, env, es));
	if (node->type == NODE_CMD)
		return (exec_cmd(node, env, es));
	if (node->type == NODE_AND || node->type == NODE_OR)
	{
		ft_putstr_fd("minishell: &&/|| not implemented yet\n", 2);
		return (1);
	}
	return (0);
}

int	executer(t_ast *ast, t_env *env, int es)
{
	int	status;

	if (!ast)
		return (1);
	status = exec_node(ast, env, es);
	return (status);
}
