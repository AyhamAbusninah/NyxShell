/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:58:09 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/11 21:05:32 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"
#include "../including/execute.h"

int	exec_pwd(t_ast *node, t_env *env)
{
	char	*cwd;

	(void)node;
	(void)env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}
