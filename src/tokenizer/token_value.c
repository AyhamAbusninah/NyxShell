/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 04:10:15 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/14 23:29:59 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/tokenizer.h"

static char	*append_segment(char *word, size_t word_len, char *str, size_t len)
{
	char	*new_word;
	size_t	x;

	new_word = (char *)malloc(word_len + len + 1);
	if (!new_word)
	{
		free(word);
		return (NULL);
	}
	x = 0;
	while (x < word_len)
	{
		new_word[x] = word[x];
		x++;
	}
	while (len--)
		new_word[x++] = *str++;
	new_word[x] = '\0';
	free(word);
	return (new_word);
}

static int	handle_quote(char *str, t_var *var, size_t *j, char *qoute)
{
	*qoute = str[var->i++];
	if (*qoute == '"')
		var->flag = 2;
	else if (*qoute == '\'' && var->flag != 2)
		var->flag = 1;
	*j = var->i;
	while (str[var->i] && str[var->i] != *qoute)
	{
		if (*qoute == '\'' && str[var->i] == '$')
			str[var->i] = NEGATIVE_DOLLAR;
		var->i++;
	}
	if (!str[var->i])
		return (0);
	return (1);
}

static char	*build_word(char *str, t_var *v, char **arr, size_t cnt)
{
	t_build_word_var	var;

	var.w = NULL;
	var.w_len = 0;
	while (str[v->i] && !is_sep(str[v->i]) && !is_space(str[v->i]))
	{
		var.qoute = 0;
		var.j = v->i;
		if (str[v->i] == '\'' || str[v->i] == '"')
		{
			if (!handle_quote(str, v, &var.j, &var.qoute))
				return (free_split_word(arr, cnt, 1));
		}
		else
			while (str[v->i] && !is_sep(str[v->i]) && !is_space(str[v->i])
				&& str[v->i] != '\'' && str[v->i] != '"')
				v->i++;
		var.w = append_segment(var.w, var.w_len, str + var.j, v->i - var.j);
		if (!var.w)
			return (free_split_word(arr, cnt, 2));
		var.w_len += v->i - var.j;
		if (var.qoute)
			v->i++;
	}
	return (var.w);
}

static char	**add_word_to_arr(char **arr, size_t count, char *word)
{
	char	**tmp;
	size_t	j;

	tmp = (char **)malloc(sizeof(char *) * (count + 2));
	if (!tmp)
	{
		free(word);
		free_split_word(arr, count, 2);
		return (NULL);
	}
	j = 0;
	while (j < count)
	{
		tmp[j] = arr[j];
		j++;
	}
	tmp[count] = word;
	tmp[count + 1] = NULL;
	free(arr);
	return (tmp);
}

char	**split_word(char *str, t_var *var)
{
	char	**final_arr;
	size_t	count;
	char	*word;

	final_arr = NULL;
	count = 0;
	while (str[var->i])
	{
		while (str[var->i] && is_space(str[var->i]))
			var->i++;
		if (!str[var->i] || is_sep(str[var->i]))
			break ;
		var->flag = 0;
		word = build_word(str, var, final_arr, count);
		if (!word)
			return (NULL);
		final_arr = add_word_to_arr(final_arr, count, word);
		if (!final_arr)
			return (NULL);
		count++;
	}
	return (final_arr);
}
