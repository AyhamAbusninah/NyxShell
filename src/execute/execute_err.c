/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:09:11 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 13:18:22 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

static int	has_slash(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (len > 0 && cmd[len - 1] == '/')
		return (1);
	return (0);
}

static int	check_path_error(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		return (print_error(cmd, ": Is a directory\n"), 126);
	if (has_slash(cmd) && stat(cmd, &st) != 0)
		return (print_error(cmd, ": Not a directory\n"), 126);
	if (access(cmd, F_OK) != 0)
		return (print_error(cmd, ": No such file or directory\n"), 127);
	if (access(cmd, X_OK) != 0)
		return (print_error(cmd, ": Permission denied\n"), 126);
	return (print_error(cmd, ": Permission denied\n"), 126);
}

int	check_cmd_error(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.' || has_slash(cmd))
		return (check_path_error(cmd));
	print_error(cmd, ": command not found\n");
	return (127);
}

void	child_clean(t_ast *node, t_env *env, char **envp, int err)
{
	if (envp)
		free_split(envp);
	free_ast(node);
	free_env(env);
	exit(err);
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (0);
}
