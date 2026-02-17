/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:58:11 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/15 17:04:35 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/built_in.h"

static void	delete_middle_node(t_env *head)
{
	head->prev->next = head->next;
	if (head->next)
		head->next->prev = head->prev;
	free(head->key);
	if (head->value)
		free(head->value);
	free(head);
}

static void	delete_head_node(t_env *head)
{
	t_env	*del;

	del = head->next;
	free(head->key);
	if (head->value)
		free(head->value);
	head->key = del->key;
	head->value = del->value;
	head->visible = del->visible;
	head->next = del->next;
	if (del->next)
		del->next->prev = head;
	free(del);
}

static void	delete_env_node(t_env *head)
{
	if (head->prev)
		delete_middle_node(head);
	else if (head->next)
		delete_head_node(head);
}

static void	unset_key(const char *key, t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
		{
			delete_env_node(head);
			break ;
		}
		head = head->next;
	}
}

int	exec_unset(t_ast *node, t_env *env)
{
	int	i;

	i = 1;
	if (!node->cmd->argv[1])
		return (1);
	while (node->cmd->argv[i])
	{
		if (check_key(node->cmd->argv[i])
			|| ft_strchr(node->cmd->argv[i], '='))
			return (1);
		i++;
	}
	i = 1;
	while (node->cmd->argv[i])
	{
		unset_key(node->cmd->argv[i], env);
		i++;
	}
	return (0);
}
