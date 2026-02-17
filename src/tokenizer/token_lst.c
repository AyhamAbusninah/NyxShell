/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:25:38 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/13 23:11:11 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/tokenizer.h"

t_token	*m_lstnew(t_token_type type, void *value, int flag)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->value = value;
	node->type = type;
	node->flag = flag;
	return (node);
}

void	m_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new || !lst)
		return ;
	new->next = NULL;
	if (*lst == NULL)
	{
		new->prev = NULL;
		*lst = new;
		return ;
	}
	last = m_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

t_token	*m_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	m_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		m_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

void	m_lstdelone(t_token *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->value);
	free(lst);
}
