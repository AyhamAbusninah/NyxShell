/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:10:34 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/15 20:32:48 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"

static int	init_av_help(t_add_argv *v, t_cmd *cmd, char **words)
{
	v->len = 0;
	while (cmd->argv && cmd->argv[v->len])
		v->len++;
	v->j = 0;
	while (words[v->j])
		v->j++;
	v->new_arr = malloc(sizeof(char *) * (v->len + v->j + 1));
	v->new_flags = malloc(sizeof(int) * (v->len + v->j));
	if (!v->new_arr || !v->new_flags)
	{
		free(v->new_arr);
		free(v->new_flags);
		return (0);
	}
	v->i = -1;
	while (++v->i < v->len)
	{
		v->new_arr[v->i] = cmd->argv[v->i];
		v->new_flags[v->i] = cmd->flags[v->i];
	}
	return (1);
}

static void	add_argv(t_cmd *cmd, char **words, int flag)
{
	t_add_argv	var;

	if (!cmd || !words)
		return ;
	if (!init_av_help(&var, cmd, words))
		return ;
	var.j = 0;
	while (words[var.j])
	{
		var.new_arr[var.i] = ft_strdup(words[var.j++]);
		var.new_flags[var.i] = flag;
		var.i++;
	}
	var.new_arr[var.i] = NULL;
	free(cmd->argv);
	free(cmd->flags);
	cmd->argv = var.new_arr;
	cmd->flags = var.new_flags;
}

static void	add_redir(t_cmd *cmd, t_redir_type type, char *target, int flag)
{
	t_redir	*new;
	t_redir	*tmp;

	if (!cmd || !target)
		return ;
	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->target = ft_strdup(target);
	new->fd = -1;
	new->next = NULL;
	new->flag = flag;
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int	handle_redir_token(t_ast *node, t_token **tok)
{
	t_redir_type	rtype;

	if ((*tok)->next && (*tok)->next->type == TOK_WORD && (*tok)->next->value
		&& (*tok)->next->value[0])
	{
		rtype = get_redir_from_tok((*tok)->type);
		add_redir(node->cmd, rtype, (*tok)->next->value[0], (*tok)->next->flag);
		if ((*tok)->next->value[1])
			add_argv(node->cmd, &(*tok)->next->value[1], (*tok)->next->flag);
		*tok = (*tok)->next->next;
		return (1);
	}
	else if (!(*tok)->next)
		return (error_msg("syntax error near unexpected token `newline'"));
	else
		*tok = (*tok)->next;
	return (0);
}

t_ast	*parse_cmd(t_token **tok)
{
	t_ast	*node;

	node = init_ast();
	if (!tok || !*tok || !node)
		return (NULL);
	node->type = NODE_CMD;
	node->cmd = init_cmd();
	if (!node->cmd)
		return (free_err_msg(node, NULL, "malloc error"));
	while (*tok && ((*tok)->type == TOK_WORD || is_redir((*tok)->type)))
	{
		if ((*tok)->type == TOK_WORD)
		{
			add_argv(node->cmd, (*tok)->value, (*tok)->flag);
			*tok = (*tok)->next;
		}
		else if (is_redir((*tok)->type))
		{
			if (!handle_redir_token(node, tok))
				return (free_err_msg(node, NULL, NULL));
		}
		else
			break ;
	}
	return (node);
}
