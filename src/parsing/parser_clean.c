/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:11:01 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/18 01:26:33 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"
#include "colors.h"

int	error_msg(char *msg)
{
	ft_putstr_fd(COLOR_ERR "NyxShell: " RESET, 2);
	ft_putstr_fd("syntax error", 2);
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n", 2);
	return (0);
}

void	free_redirs(t_redir *r)
{
	t_redir	*tmp;

	while (r)
	{
		tmp = r->next;
		free(r->target);
		free(r);
		r = tmp;
	}
}

void	free_ast(t_ast *ast)
{
	int	i;

	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	if (ast->type == NODE_CMD && ast->cmd)
	{
		if (ast->cmd->argv)
		{
			i = 0;
			while (ast->cmd->argv[i])
			{
				free(ast->cmd->argv[i]);
				i++;
			}
			free(ast->cmd->argv);
		}
		free(ast->cmd->flags);
		free_redirs(ast->cmd->redir);
		free(ast->cmd);
	}
	free(ast);
}

t_ast	*free_err_msg(t_ast *left, t_ast *right, char *msg)
{
	if (left)
		free_ast(left);
	if (right)
		free_ast(right);
	if (msg)
		error_msg(msg);
	return (NULL);
}
