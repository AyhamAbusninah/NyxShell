/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by aabusnin          #+#    #+#             */
/*   Updated: 2026/02/18 00:00:00 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/* ── ANSI Base Colors ──────────────────────────────────── */
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define MAGENTA		"\033[0;35m"
# define CYAN			"\033[0;36m"
# define WHITE			"\033[0;37m"
# define RESET			"\033[0m"
# define BOLD			"\033[1m"

/* ── Semantic Colors ───────────────────────────────────── */
# define COLOR_ERR		"\033[1;31m"
# define COLOR_PRMPT_USER	"\033[0;36m"
# define COLOR_PRMPT_DIR	"\033[1;34m"
# define COLOR_PRMPT_AT	"\033[0;35m"
# define COLOR_PRMPT_SHELL	"\033[1;32m"
# define COLOR_PRMPT_DOLLAR	"\033[1;33m"
# define COLOR_LOGO		"\033[1;35m"
# define COLOR_LOGO_ALT	"\033[0;36m"
# define COLOR_READY	"\033[1;33m"

#endif
