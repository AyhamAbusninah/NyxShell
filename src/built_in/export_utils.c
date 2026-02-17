/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:45:00 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/11 19:48:55 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/built_in.h"

int	is_dup(char *key, t_env *head)
{
	t_env	*env;

	env = head;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	check_key(char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A' || str[0] > 'Z')
		&& str[0] != '_')
		return (1);
	i = 1;
	while (str[i])
	{
		if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9') && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
	return (0);
}

int	init_export(t_export *e)
{
	e->i = 0;
	e->k_v = malloc(sizeof(char *) * 2);
	if (!e->k_v)
		return (1);
	e->k_v[0] = NULL;
	e->k_v[1] = NULL;
	return (0);
}
