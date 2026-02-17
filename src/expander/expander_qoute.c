/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_qoute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:39:50 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/08 13:33:23 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/parser.h"
#include "../including/execute.h"

char	*expand_heredoc_line(char *line, t_env *env, int exit_status)
{
	return (expand_string(line, env, exit_status));
}

static char	*expand_token_word(char *word, int flag, t_env *env, int es)
{
	if (flag == 1)
		return (ft_strdup(word));
	return (expand_string(word, env, es));
}

static int	count_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

static char	**remove_empty_arg(char **argv, int pos, int len)
{
	int		i;
	int		j;
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * len);
	if (!new_argv)
		return (argv);
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (i != pos)
		{
			new_argv[j] = argv[i];
			j++;
		}
		else
			free(argv[i]);
		i++;
	}
	new_argv[j] = NULL;
	free(argv);
	return (new_argv);
}

void	expand_and_clean_argv(t_cmd *cmd, t_env *env, int es, int flag)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (flag != 1 && ft_strchr(cmd->argv[i], '$'))
		{
			expanded = expand_token_word(cmd->argv[i], flag, env, es);
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
		}
		if (flag == 0 && cmd->argv[i][0] == '\0')
		{
			cmd->argv = remove_empty_arg(cmd->argv, i, count_argv(cmd->argv));
			continue ;
		}
		i++;
	}
}
