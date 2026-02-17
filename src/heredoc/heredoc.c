/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 22:46:42 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/16 20:54:26 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

static int	check_write(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) < 0)
		return (0);
	if (write(fd, "\n", 1) < 0)
		return (0);
	return (1);
}

static int	update_line(char **line, int exp, t_env *env, int es)
{
	char	*expanded;

	if (exp == 1 || exp == 2)
		return (0);
	expanded = expand_heredoc_line(*line, env, es);
	free(*line);
	*line = expanded;
	return (1);
}

static int	hd_read_loop(int wfd, char *delim, int quoted, void *env_es[2])
{
	char	*line;

	heredoc_sig();
	while (!g_sig)
	{
		line = readline("heredoc> ");
		if (g_sig)
			return (free_heredoc(line, 0));
		if (!line)
			return (1);
		if (ft_strcmp(line, delim) == 0)
			return (free_heredoc(line, 1));
		update_line(&line, quoted, (t_env *)env_es[0], *(int *)env_es[1]);
		if (!check_write(wfd, line))
			return (free_heredoc(line, 0));
		free(line);
	}
	return (0);
}

static int	handle_one_heredoc(t_redir *r, t_env *env, int exit_status)
{
	int		pfd[2];
	int		result;
	void	*env_es[2];

	if (!r || !r->target)
		return (0);
	if (pipe(pfd) < 0)
		return (0);
	env_es[0] = env;
	env_es[1] = &exit_status;
	result = hd_read_loop(pfd[1], r->target,
			r->flag, env_es);
	heredoc_sig_restore();
	close(pfd[1]);
	if (!result || g_sig)
	{
		close(pfd[0]);
		return (0);
	}
	r->fd = pfd[0];
	return (1);
}

int	heredoc_handler(t_ast *node, t_env *env, int exit_status)
{
	t_redir	*r;

	if (!node)
		return (1);
	if (node->type != NODE_CMD)
	{
		if (node->left)
			if (!heredoc_handler(node->left, env, exit_status))
				return (0);
		if (node->right)
			if (!heredoc_handler(node->right, env, exit_status))
				return (0);
		return (1);
	}
	if (!node->cmd)
		return (1);
	r = node->cmd->redir;
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
			if (!handle_one_heredoc(r, env, exit_status))
				return (0);
		r = r->next;
	}
	return (1);
}
