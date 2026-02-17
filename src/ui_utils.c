/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/18 01:27:27 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "including/colors.h"
#include "including/execute.h"

static void	print_logo_top(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(COLOR_LOGO, 1);
	ft_putstr_fd("    ╔═╗╔╦╗╔═╗  ╔═╦ ╦╔═╗╦  ╦  \n", 1);
	ft_putstr_fd("    ║║║ ║ ╠═╝  ╚═╗╠═╣║╣ ║  ║  \n", 1);
	ft_putstr_fd("    ╝╚╝ ╩ ╩    ╚═╝╩ ╩╚═╝╩═╝╩═╝\n", 1);
	ft_putstr_fd(RESET, 1);
}

static void	print_logo_art(void)
{
	ft_putstr_fd(COLOR_LOGO_ALT, 1);
	ft_putstr_fd("    ███╗   ██╗██╗   ██╗██╗  ██╗\n", 1);
	ft_putstr_fd("    ████╗  ██║╚██╗ ██╔╝╚██╗██╔╝\n", 1);
	ft_putstr_fd("    ██╔██╗ ██║ ╚████╔╝  ╚███╔╝ \n", 1);
	ft_putstr_fd("    ██║╚██╗██║  ╚██╔╝   ██╔██╗ \n", 1);
	ft_putstr_fd("    ██║ ╚████║   ██║   ██╔╝ ██╗\n", 1);
	ft_putstr_fd("    ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝\n", 1);
	ft_putstr_fd(RESET, 1);
}

void	print_startup_logo(void)
{
	print_logo_art();
	print_logo_top();
	ft_putstr_fd(COLOR_READY, 1);
	ft_putstr_fd("    >>> System Ready <<<\n", 1);
	ft_putstr_fd(RESET, 1);
	ft_putstr_fd("\n", 1);
}

static char	*get_short_dir(char *cwd)
{
	char	*last_slash;

	if (!cwd)
		return (ft_strdup("?"));
	if (ft_strcmp(cwd, "/") == 0)
		return (ft_strdup("/"));
	last_slash = ft_strrchr(cwd, '/');
	if (last_slash && *(last_slash + 1))
		return (ft_strdup(last_slash + 1));
	return (ft_strdup(cwd));
}

static char	*build_prompt_str(char *user, char *dir)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strdup("\001" COLOR_PRMPT_USER "\002");
	tmp = ft_strjoin(prompt, user);
	free(prompt);
	prompt = ft_strjoin(tmp, "\001" COLOR_PRMPT_AT "\002@");
	free(tmp);
	tmp = ft_strjoin(prompt, "\001" COLOR_PRMPT_SHELL "\002NyxShell");
	free(prompt);
	prompt = ft_strjoin(tmp, "\001" RESET "\002:");
	free(tmp);
	tmp = ft_strjoin(prompt, "\001" COLOR_PRMPT_DIR "\002");
	free(prompt);
	prompt = ft_strjoin(tmp, dir);
	free(tmp);
	tmp = ft_strjoin(prompt, "\001" COLOR_PRMPT_DOLLAR "\002$ ");
	free(prompt);
	prompt = ft_strjoin(tmp, "\001" RESET "\002");
	free(tmp);
	return (prompt);
}

char	*get_prompt(t_env *env)
{
	char	cwd[4096];
	char	*user;
	char	*dir;
	char	*prompt;

	user = get_env_value(env, "USER");
	if (!user)
		user = "nyx";
	if (!getcwd(cwd, sizeof(cwd)))
		dir = ft_strdup("?");
	else
		dir = get_short_dir(cwd);
	if (!dir)
		return (ft_strdup("NyxShell$ "));
	prompt = build_prompt_str(user, dir);
	free(dir);
	if (!prompt)
		return (ft_strdup("NyxShell$ "));
	return (prompt);
}
