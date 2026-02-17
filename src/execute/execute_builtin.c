/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:35:21 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/16 20:42:13 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

int	is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strcmp(arg, "echo") == 0)
		return (1);
	if (ft_strcmp(arg, "cd") == 0)
		return (1);
	if (ft_strcmp(arg, "pwd") == 0)
		return (1);
	if (ft_strcmp(arg, "unset") == 0)
		return (1);
	if (ft_strcmp(arg, "export") == 0)
		return (1);
	if (ft_strcmp(arg, "env") == 0)
		return (1);
	if (ft_strcmp(arg, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_ast *node, t_env *env, int es)
{
	char	*cmd;

	cmd = node->cmd->argv[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (exec_echo(node, env));
	if (ft_strcmp(cmd, "cd") == 0)
		return (exec_cd(node, env));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (exec_pwd(node, env));
	if (ft_strcmp(cmd, "unset") == 0)
		return (exec_unset(node, env));
	if (ft_strcmp(cmd, "export") == 0)
		return (exec_export(node, env));
	if (ft_strcmp(cmd, "env") == 0)
		return (exec_env(node, env));
	if (ft_strcmp(cmd, "exit") == 0)
		return (exec_exit(node, es));
	return (1);
}
