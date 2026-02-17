/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:15:20 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 15:01:53 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"

int	is_redir(t_token_type type)
{
	if (type == TOK_REDIR_IN || type == TOK_REDIR_OUT || type == TOK_HEREDOC
		|| type == TOK_REDIR_APPEND)
		return (1);
	return (0);
}
