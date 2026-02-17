/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_find_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:57:14 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 00:00:30 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**split_path(char **envp)
{
	char	**split_p;
	char	*path;

	path = get_path_from_env(envp);
	if (!path)
		return (NULL);
	split_p = ft_split(path, ':');
	if (!split_p)
		return (NULL);
	return (split_p);
}

void	free_split(char **split_p)
{
	int	i;

	i = 0;
	while (split_p[i])
	{
		free(split_p[i]);
		i++;
	}
	free(split_p);
}

static char	*path_with_slash(char *path)
{
	char	*result;

	result = ft_strjoin(path, "/");
	return (result);
}

char	**add_slash(char **envp)
{
	char	**path;
	char	**path_slash;
	int		i;
	int		len;

	path = split_path(envp);
	if (!path)
		return (NULL);
	len = 0;
	while (path[len])
		len++;
	path_slash = malloc(sizeof(char *) * (len + 1));
	if (!path_slash)
		return (NULL);
	i = 0;
	while (path[i])
	{
		path_slash[i] = path_with_slash(path[i]);
		if (!path_slash[i])
			return (NULL);
		i++;
	}
	path_slash[i] = NULL;
	free_split(path);
	return (path_slash);
}
