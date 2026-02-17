/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:58:40 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/13 16:36:33 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "execute.h"
# include "parser.h"

int	is_dup(char *key, t_env *head);
int	update_envlst(t_env **head, char **k_v, int flag);
int	check_key(char *str);
int	print_export(t_env *env);
int	init_export(t_export *e);

#endif