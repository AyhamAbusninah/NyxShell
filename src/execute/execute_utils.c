/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:08:03 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/18 01:26:33 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"
#include "../including/colors.h"

static int	env_size(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		if (env->visible)
			len++;
		env = env->next;
	}
	return (len);
}

static char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**env_to_char(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->visible)
		{
			envp[i] = join_key_value(env->key, env->value);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	print_error(char *cmd, char *msg)
{
	ft_putstr_fd(COLOR_ERR "NyxShell: " RESET, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
}

int	apply_redirs(t_redir *r)
{
	int	fd;

	while (r)
	{
		fd = open_redir(r);
		if (fd < 0)
		{
			ft_putstr_fd(COLOR_ERR "NyxShell: " RESET, 2);
			perror(r->target);
			return (0);
		}
		if (!redir_fd(r, fd))
			return (0);
		r = r->next;
	}
	return (1);
}
