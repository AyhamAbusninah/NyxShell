/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:58:02 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/13 16:32:34 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/built_in.h"

int	exec_env(t_ast *node, t_env *p_env)
{
	(void)node;
	while (p_env != NULL)
	{
		if (p_env->value != NULL)
			printf ("%s=%s\n", p_env->key, p_env->value);
		p_env = p_env->next;
	}
	return (0);
}
