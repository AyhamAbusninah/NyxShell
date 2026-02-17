/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utlits2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:31:32 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/14 20:08:18 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/tokenizer.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

int	is_sep(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '('
		|| c == ')');
}

char	*free_split_word(char **arr, size_t n, int error)
{
	size_t	i;

	if (error == 1)
		ft_putendl_fd("syntax error: unclosed quote", 2);
	else if (error == 2)
		ft_putendl_fd("malloc error", 2);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
		free(arr[i++]);
	free(arr);
	return (NULL);
}
