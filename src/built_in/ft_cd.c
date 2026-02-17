/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:57:52 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/15 20:34:24 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../including/built_in.h"

int	free_fire(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (1);
}

int	free_cd(char *opwd, char *dest)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(dest);
	return (free_fire(opwd, dest));
}

void	update_pwd(char *s1, char *s2, int *i, t_env *env)
{
	char	*k_v[2];

	if (!*i)
	{
		k_v[0] = ft_strdup("OLDPWD");
		k_v[1] = ft_strdup(s1);
	}
	else if (*i)
	{
		k_v[0] = ft_strdup("PWD");
		k_v[1] = ft_strdup(s2);
	}
	update_envlst(&env, k_v, 1);
	free_fire(k_v[0], k_v[1]);
	(*i)++;
}

int	to_home(t_env *env)
{
	char	*home;
	int		i;
	char	*opwd;

	home = get_env_value(env, "HOME");
	if (!home)
		return (1);
	opwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
		return (free_fire(home, opwd));
	i = 0;
	while (i < 2)
		update_pwd(opwd, home, &i, env);
	free_fire(opwd, home);
	return (0);
}

int	exec_cd(t_ast *node, t_env *env)
{
	int		i;
	char	*opwd;
	char	*dest;
	char	*npwd;

	i = 0;
	if (!node->cmd->argv[1])
		return (to_home(env));
	dest = ft_strdup(node->cmd->argv[1]);
	if (!dest)
		return (1);
	opwd = getcwd(NULL, 0);
	if (node->cmd->argv[2] != NULL)
		return (free_fire(dest, opwd));
	if (chdir(dest) == -1)
		return (free_cd(opwd, dest));
	npwd = getcwd(NULL, 0);
	if (!npwd)
		return (free_cd(opwd, dest));
	while (i < 2)
		update_pwd(opwd, npwd, &i, env);
	free(dest);
	free_fire(opwd, npwd);
	return (0);
}
