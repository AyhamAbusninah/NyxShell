/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:39:26 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 15:07:59 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"
#include "../including/execute.h"

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->visible = 1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	parse_env_str(char *env_str, char **key, char **value)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	*key = ft_substr(env_str, 0, i);
	if (env_str[i] == '=')
		*value = ft_strdup(env_str + i + 1);
	else
		*value = NULL;
}

void	add_env_var(t_env **head, char *env_str)
{
	t_env	*new_node;
	t_env	*tmp;
	char	*key;
	char	*value;

	parse_env_str(env_str, &key, &value);
	new_node = new_env_node(key, value);
	free(key);
	free(value);
	if (!*head)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		add_env_var(&head, envp[i]);
		i++;
	}
	return (head);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			return (ft_strdup(""));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
