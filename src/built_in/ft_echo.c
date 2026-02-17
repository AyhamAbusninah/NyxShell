/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:57:59 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/15 17:24:06 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/built_in.h"

int	check_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	exec_echo(t_ast *node, t_env *env)
{
	int	i;
	int	nl;

	(void)env;
	nl = 1;
	i = 1;
	while (node->cmd->argv[i] && check_n_option(node->cmd->argv[i]))
	{
		nl = 0;
		i++;
	}
	while (node->cmd->argv[i])
	{
		ft_putstr_fd(node->cmd->argv[i], 1);
		if (node->cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
