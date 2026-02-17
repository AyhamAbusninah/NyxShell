/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:07:47 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/16 20:42:13 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

int	open_redir(t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == REDIR_IN)
		fd = open(r->target, O_RDONLY);
	else if (r->type == REDIR_OUT)
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == REDIR_APPEND)
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (r->type == REDIR_HEREDOC)
		fd = r->fd;
	return (fd);
}

int	redir_fd(t_redir *r, int fd)
{
	int	target_fd;

	target_fd = STDOUT_FILENO;
	if (r->type == REDIR_IN || r->type == REDIR_HEREDOC)
		target_fd = STDIN_FILENO;
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		return (0);
	}
	close(fd);
	return (1);
}

static void	child_exec(t_ast *node, t_env *env, int es)
{
	char	*path;
	char	**envp;

	reset_signals();
	if (!apply_redirs(node->cmd->redir))
		child_clean(node, env, NULL, 1);
	if (is_builtin(node->cmd->argv[0]))
		child_clean(node, env, NULL, exec_builtin(node, env, es));
	envp = env_to_char(env);
	path = find_command(node->cmd->argv[0], envp);
	if (!path)
		child_clean(node, env, envp, check_cmd_error(node->cmd->argv[0]));
	execve(path, node->cmd->argv, envp);
	perror("execve");
	free(path);
	child_clean(node, env, envp, 126);
}

static int	exec_builtin_redir(t_ast *node, t_env *env, int es)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (!apply_redirs(node->cmd->redir))
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	ret = exec_builtin(node, env, es);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (ret);
}

int	exec_cmd(t_ast *node, t_env *env, int es)
{
	int	pid;
	int	status;

	if (!node->cmd || !node->cmd->argv || !node->cmd->argv[0])
		return (0);
	if (is_builtin(node->cmd->argv[0]))
		return (exec_builtin_redir(node, env, es));
	pid = fork();
	if (pid < 0)
		return (ft_perror("fork", 1));
	if (pid == 0)
	{
		reset_signals();
		child_exec(node, env, es);
	}
	signals_ignore();
	waitpid(pid, &status, 0);
	setup_signals();
	return (get_exit_code(status));
}
