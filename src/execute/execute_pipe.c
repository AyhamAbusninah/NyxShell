/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:07:34 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/16 20:42:13 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

int	ft_perror(const char *msg, int ret)
{
	perror(msg);
	return (ret);
}

static void	child_left(t_var_pipe *var, t_ast *node, t_env *env, int es)
{
	reset_signals();
	close(var->pfd[0]);
	dup2(var->pfd[1], STDOUT_FILENO);
	close(var->pfd[1]);
	exit(exec_node(node->left, env, es));
}

static void	child_right(t_var_pipe *var, t_ast *node, t_env *env, int es)
{
	reset_signals();
	close(var->pfd[1]);
	dup2(var->pfd[0], STDIN_FILENO);
	close(var->pfd[0]);
	exit(exec_node(node->right, env, es));
}

static int	fork_right(t_var_pipe *var, t_ast *node, t_env *env, int es)
{
	var->pid_right = fork();
	if (var->pid_right < 0)
	{
		close(var->pfd[0]);
		close(var->pfd[1]);
		return (ft_perror("fork", 1));
	}
	if (var->pid_right == 0)
		child_right(var, node, env, es);
	return (0);
}

int	exec_pipe(t_ast *node, t_env *env, int es)
{
	t_var_pipe	var;

	if (pipe(var.pfd) == -1)
		return (ft_perror("pipe", 1));
	var.pid_left = fork();
	if (var.pid_left < 0)
	{
		close(var.pfd[0]);
		close(var.pfd[1]);
		return (ft_perror("fork", 1));
	}
	if (var.pid_left == 0)
		child_left(&var, node, env, es);
	if (fork_right(&var, node, env, es))
		return (1);
	close(var.pfd[0]);
	close(var.pfd[1]);
	signals_ignore();
	waitpid(var.pid_left, NULL, 0);
	waitpid(var.pid_right, &var.status, 0);
	setup_signals();
	return (get_exit_code(var.status));
}
