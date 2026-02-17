/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:39:11 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 23:29:43 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"
#include "../including/execute.h"

static void	restore_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == NEGATIVE_DOLLAR)
			str[i] = '$';
		i++;
	}
}

void	expand_cmd_args(t_cmd *cmd, t_env *env, int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '$'))
		{
			expanded = expand_string(cmd->argv[i], env, exit_status);
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
		}
		restore_dollars(cmd->argv[i]);
		i++;
	}
}

static void	expand_redir_targets(t_redir *r, t_env *env, int es)
{
	char	*expanded;

	while (r)
	{
		if (r->type != REDIR_HEREDOC && ft_strchr(r->target, '$'))
		{
			expanded = expand_string(r->target, env, es);
			free(r->target);
			r->target = expanded;
		}
		restore_dollars(r->target);
		r = r->next;
	}
}

void	free_expand_ast(t_ast *node, t_env *env, int exit_status)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD && node->cmd)
	{
		expand_cmd_args(node->cmd, env, exit_status);
		expand_redir_targets(node->cmd->redir, env, exit_status);
	}
	free_expand_ast(node->left, env, exit_status);
	free_expand_ast(node->right, env, exit_status);
}

void	expand_ast(t_ast *node, t_env *env, int exit_status)
{
	free_expand_ast(node, env, exit_status);
}
