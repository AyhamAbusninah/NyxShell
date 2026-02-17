/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:03:45 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/14 15:06:58 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/execute.h"
#include "../including/parser.h"

static char	*build_full_path(char *path, char *cmd)
{
	char	*full_path;

	full_path = ft_strjoin(path, cmd);
	return (full_path);
}

static char	*return_freed_str(char **str, char *full_path)
{
	free_split(str);
	return (full_path);
}

static int	is_regular(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (0);
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*find_command(char *cmd, char **envp)
{
	char	**path;
	char	*full_path;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (is_regular(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = add_slash(envp);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		full_path = build_full_path(path[i], cmd);
		if (is_regular(full_path))
			return (return_freed_str(path, full_path));
		free(full_path);
		i++;
	}
	free_split(path);
	return (NULL);
}
