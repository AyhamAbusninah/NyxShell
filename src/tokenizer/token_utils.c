/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:22:01 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/13 23:11:11 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/tokenizer.h"

void	free_split_void(void *p)
{
	char	**v;
	int		i;

	v = (char **)p;
	if (!v)
		return ;
	i = 0;
	while (v[i])
		free(v[i++]);
	free(v);
}

t_token	*free_all(t_token *lst, char **value)
{
	int	i;

	m_lstclear(&lst, free_split_void);
	if (value)
	{
		i = 0;
		while (value[i])
			free(value[i++]);
		free(value);
	}
	return (NULL);
}

void	token_prepare(t_var *var)
{
	var->i = 0;
	var->final_lst = NULL;
	var->node = NULL;
	var->value = NULL;
	var->type = 0;
	var->flag = 0;
}
