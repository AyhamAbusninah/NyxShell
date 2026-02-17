/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:58:05 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/16 20:42:13 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/built_in.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exec_exit(t_ast *node, int es)
{
	int	e_code;

	if (!node->cmd->argv[1])
		exit(es);
	if (node->cmd->argv[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (node->cmd->argv[1] != NULL)
	{
		if (!is_numeric(node->cmd->argv[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(2);
		}
		e_code = ft_atoi(node->cmd->argv[1]);
		exit(e_code % 256);
	}
	exit(es);
}
