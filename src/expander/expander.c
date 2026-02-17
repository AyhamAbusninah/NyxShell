/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:31:28 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/08 20:10:17 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"
#include "../including/execute.h"

static char	*expand_var(char *str, int *i, t_env *env, int exit_status)
{
	int		len;
	char	*var_name;
	char	*val;

	(*i)++;
	len = get_var_len(&str[*i]);
	var_name = ft_substr(str, *i, len);
	val = get_env_val(var_name, env, exit_status);
	free(var_name);
	*i += len;
	return (val);
}

static int	is_expandable(char *str, int i)
{
	if (str[i] == '$' && str[i + 1])
	{
		if (is_valid_var_char(str[i + 1]) || str[i + 1] == '?')
			return (1);
	}
	return (0);
}

static int	get_len_exp(char *str, t_env *env, int es)
{
	int		len;
	int		i;
	char	*val;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (is_expandable(str, i))
		{
			val = expand_var(str, &i, env, es);
			len += ft_strlen(val);
			free(val);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	fill_var(char *dst, int *j, char *val)
{
	int	k;

	k = 0;
	while (val[k])
	{
		dst[(*j)] = val[k];
		(*j)++;
		k++;
	}
}

char	*expand_string(char *str, t_env *env, int exit_status)
{
	char	*result;
	char	*val;
	int		i;
	int		j;

	result = malloc(get_len_exp(str, env, exit_status) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_expandable(str, i))
		{
			val = expand_var(str, &i, env, exit_status);
			fill_var(result, &j, val);
			free(val);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
