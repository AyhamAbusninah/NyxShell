/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:00:00 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/18 01:26:33 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "including/parser.h"
#include "including/execute.h"
#include "including/colors.h"

static int	process_line(char *line, t_env *env, int exit_status)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = tokenizer(line);
	if (!tokens)
		return (exit_status);
	ast = parser(tokens);
	m_lstclear(&tokens, free_split_void);
	if (!ast)
		return (2);
	if (!heredoc_handler(ast, env, exit_status))
	{
		free_ast(ast);
		return (130);
	}
	expand_ast(ast, env, exit_status);
	exit_status = executer(ast, env, exit_status);
	free_ast(ast);
	return (exit_status);
}

static int	check_signal_status(int exit_status)
{
	if (g_sig)
	{
		exit_status = g_sig;
		g_sig = 0;
	}
	return (exit_status);
}

static int	handle_line(char *line, t_env *env, int exit_status)
{
	add_history(line);
	exit_status = process_line(line, env, exit_status);
	free(line);
	return (exit_status);
}

static void	minishell_loop(t_env *env)
{
	char	*line;
	char	*prompt;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		setup_signals();
		prompt = get_prompt(env);
		line = readline(prompt);
		free(prompt);
		exit_status = check_signal_status(exit_status);
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		exit_status = handle_line(line, env, exit_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
	{
		ft_putstr_fd(COLOR_ERR "NyxShell: " RESET
			"failed to init env\n", 2);
		return (1);
	}
	print_startup_logo();
	minishell_loop(env);
	free_env(env);
	return (0);
}
