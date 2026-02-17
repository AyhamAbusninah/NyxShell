/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:58:07 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/15 17:21:45 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/built_in.h"

static int	add_env_node(t_env **head, t_env *new_node)
{
	t_env	*cur;

	if (!*head)
	{
		*head = new_node;
		return (0);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
	new_node->prev = cur;
	return (0);
}

int	update_envlst(t_env **head, char **k_v, int flag)
{
	t_env	*new_node;
	t_env	*cur;

	if (is_dup(k_v[0], *head))
	{
		cur = *head;
		while (cur && ft_strcmp(cur->key, k_v[0]) != 0)
			cur = cur->next;
		if (cur)
		{
			free(cur->value);
			if (flag == 1)
				cur->value = ft_strdup(k_v[1]);
			else
				cur->value = NULL;
		}
		return (0);
	}
	if (flag == 1)
		new_node = new_env_node(k_v[0], k_v[1]);
	else
		new_node = new_env_node(k_v[0], NULL);
	if (!new_node)
		return (1);
	return (add_env_node(head, new_node));
}

static int	parse_export_arg(char *arg, t_export *e)
{
	int	i;

	e->i = 0;
	while (arg[e->i] != '\0' && arg[e->i] != '=')
		e->i++;
	e->key_to_check = ft_substr(arg, 0, e->i);
	if (check_key(e->key_to_check))
	{
		free(e->key_to_check);
		return (1);
	}
	e->k_v[0] = ft_substr(arg, 0, e->i);
	e->j = e->i;
	free(e->key_to_check);
	if (arg[e->i] == '\0')
		return (0);
	i = e->i;
	while (arg[i] != '\0')
		i++;
	e->k_v[1] = ft_substr(arg, e->j + 1, i - e->j - 1);
	return (0);
}

static int	process_args(char **av, t_env *env_head, t_export *e)
{
	int	i;
	int	flag;

	i = 1;
	while (av[i])
	{
		if (parse_export_arg(av[i], e))
		{
			free(e->k_v[0]);
			free(e->k_v[1]);
			return (1);
		}
		flag = 0;
		if (e->k_v[1] != NULL)
			flag = 1;
		update_envlst(&env_head, e->k_v, flag);
		free(e->k_v[0]);
		e->k_v[0] = NULL;
		free(e->k_v[1]);
		e->k_v[1] = NULL;
		i++;
	}
	return (0);
}

int	exec_export(t_ast *node, t_env *env_head)
{
	t_export	e;

	if (init_export(&e))
		return (1);
	if (!node->cmd->argv[1])
	{
		print_export(env_head);
		free(e.k_v);
		return (0);
	}
	if (process_args(node->cmd->argv, env_head, &e))
	{
		free(e.k_v);
		print_error("export: not a valid identifier\n", node->cmd->argv[e.i]);
		return (1);
	}
	free(e.k_v);
	return (0);
}
