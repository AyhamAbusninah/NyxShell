/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:46:47 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/16 20:58:44 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

int	g_sig = 0;

int	free_heredoc(char *line, int ret)
{
	free(line);
	return (ret);
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_sig = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(STDIN_FILENO);
}

void	heredoc_sig(void)
{
	g_sig = 0;
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_sig_restore(void)
{
	int	fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (g_sig)
	{
		fd = open("/dev/tty", O_RDWR);
		if (fd >= 0)
			dup2(fd, STDIN_FILENO);
		if (fd > 2)
			close(fd);
	}
}
