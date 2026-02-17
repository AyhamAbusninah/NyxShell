/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:38:56 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/08 18:50:40 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"
#include "../including/execute.h"

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_val(char *var_name, t_env *env, int last_exit_status)
{
	t_env	*tmp;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(last_exit_status));
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var_name) == 0)
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			return (ft_strdup(""));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	return (i);
}
