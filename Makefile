# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/04 10:00:00 by aabusnin          #+#    #+#              #
#    Updated: 2026/02/18 01:30:51 by aabusnin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ── Colors ────────────────────────────────────────────────
C_RESET		= \033[0m
C_BOLD		= \033[1m
C_RED		= \033[1;31m
C_GREEN		= \033[1;32m
C_YELLOW	= \033[1;33m
C_BLUE		= \033[1;34m
C_MAGENTA	= \033[1;35m
C_CYAN		= \033[1;36m
C_DIM		= \033[2m

# ── Progress bar helpers ──────────────────────────────────
SRC_COUNT	= 0
SRC_TOTAL	= $(words $(ALL_SRC))
BAR_DONE	= █
BAR_TODO	= ░

define progress
	$(eval SRC_COUNT = $(shell echo $$(($(SRC_COUNT) + 1))))
	$(eval PERCENT = $(shell echo $$(($(SRC_COUNT) * 100 / $(SRC_TOTAL)))))
	$(eval FILLED = $(shell echo $$(($(SRC_COUNT) * 30 / $(SRC_TOTAL)))))
	$(eval EMPTY = $(shell echo $$((30 - $(FILLED)))))
	@printf "\r$(C_CYAN)  [CC]$(C_RESET) $(C_DIM)%-40s$(C_RESET) $(C_GREEN)%s$(C_DIM)%s$(C_RESET) $(C_YELLOW)%3d%%$(C_RESET)" \
		"$(notdir $<)" \
		"$$(printf '$(BAR_DONE)%.0s' $$(seq 1 $(FILLED) 2>/dev/null))" \
		"$$(printf '$(BAR_TODO)%.0s' $$(seq 1 $(EMPTY) 2>/dev/null))" \
		"$(PERCENT)"
endef

# ── Project ───────────────────────────────────────────────
NAME = nyxshell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRC_DIR = src
LIBFT_DIR = $(SRC_DIR)/libft
TOK_DIR = $(SRC_DIR)/tokenizer
PARSE_DIR = $(SRC_DIR)/parsing
EXPAND_DIR = $(SRC_DIR)/expander
HEREDOC_DIR = $(SRC_DIR)/heredoc
EXEC_DIR = $(SRC_DIR)/execute
SIGNAL_DIR = $(SRC_DIR)/signals
BUILTIN_DIR = $(SRC_DIR)/built_in

TOK_SRC = $(TOK_DIR)/tokenizer.c \
		  $(TOK_DIR)/token_lst.c \
		  $(TOK_DIR)/token_type.c \
		  $(TOK_DIR)/token_utils.c \
		  $(TOK_DIR)/token_utlits2.c \
		  $(TOK_DIR)/token_value.c

PARSE_SRC = $(PARSE_DIR)/parser.c \
			$(PARSE_DIR)/parser_or.c \
			$(PARSE_DIR)/parser_and.c \
			$(PARSE_DIR)/parser_pipe.c \
			$(PARSE_DIR)/parser_cmd.c \
			$(PARSE_DIR)/parser_node.c \
			$(PARSE_DIR)/parser_utils.c \
			$(PARSE_DIR)/parser_clean.c

EXPAND_SRC = $(EXPAND_DIR)/expander.c \
			 $(EXPAND_DIR)/expander_env.c \
			 $(EXPAND_DIR)/expander_utils.c \
			 $(EXPAND_DIR)/expander_qoute.c \
			 $(EXPAND_DIR)/expander_clean.c \
			 $(EXPAND_DIR)/expander_err.c

HEREDOC_SRC = $(HEREDOC_DIR)/heredoc.c \
			  $(HEREDOC_DIR)/heredoc_utils.c

EXEC_SRC = $(EXEC_DIR)/execute.c \
		   $(EXEC_DIR)/execute_cmd.c \
		   $(EXEC_DIR)/execute_pipe.c \
		   $(EXEC_DIR)/execute_builtin.c \
		   $(EXEC_DIR)/execute_find_path.c \
		   $(EXEC_DIR)/execute_utils.c \
		   $(EXEC_DIR)/execute_err.c \
		   $(EXEC_DIR)/find_cmd.c 

SIGNAL_SRC = $(SIGNAL_DIR)/signal.c

BUILTIN_SRC = $(BUILTIN_DIR)/export_utils.c \
			  $(BUILTIN_DIR)/ft_export.c \
			  $(BUILTIN_DIR)/ft_cd.c \
			  $(BUILTIN_DIR)/ft_env.c \
			  $(BUILTIN_DIR)/ft_pwd.c \
			  $(BUILTIN_DIR)/ft_echo.c \
			  $(BUILTIN_DIR)/ft_exit.c \
			  $(BUILTIN_DIR)/ft_unset.c

MAIN_SRC = $(SRC_DIR)/main.c
UI_SRC = $(SRC_DIR)/ui_utils.c


LIBFT = $(LIBFT_DIR)/libft.a

ALL_SRC = $(TOK_SRC) $(PARSE_SRC) $(EXPAND_SRC) $(HEREDOC_SRC) $(EXEC_SRC) \
		  $(SIGNAL_SRC) $(MAIN_SRC) $(UI_SRC) $(BUILTIN_SRC)
OBJ = $(ALL_SRC:.c=.o)

INC = -I$(SRC_DIR)/including -I$(LIBFT_DIR)

# ── Targets ───────────────────────────────────────────────
all: header $(NAME)
	@echo ""
	@echo ""
	@printf "  $(C_GREEN)$(C_BOLD)✓ Build successful!$(C_RESET)\n"
	@printf "  $(C_DIM)Run with: $(C_RESET)$(C_CYAN)./$(NAME)$(C_RESET)\n"
	@echo ""

header:
	@echo ""
	@printf "  $(C_MAGENTA)$(C_BOLD)╔══════════════════════════════════════╗$(C_RESET)\n"
	@printf "  $(C_MAGENTA)$(C_BOLD)║       $(C_CYAN)  N Y X S H E L L             $(C_MAGENTA)$(C_BOLD)║$(C_RESET)\n"
	@printf "  $(C_MAGENTA)$(C_BOLD)║       $(C_DIM)  Building...                  $(C_MAGENTA)$(C_BOLD)║$(C_RESET)\n"
	@printf "  $(C_MAGENTA)$(C_BOLD)╚══════════════════════════════════════╝$(C_RESET)\n"
	@echo ""

$(LIBFT):
	@printf "  $(C_BLUE)$(C_BOLD)[LIB]$(C_RESET) $(C_DIM)Compiling libft...$(C_RESET)\n"
	@make -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1
	@printf "  $(C_GREEN)$(C_BOLD)[LIB]$(C_RESET) libft.a ready\n\n"

$(NAME): $(LIBFT) $(OBJ)
	@echo ""
	@printf "  $(C_YELLOW)$(C_BOLD)[LINK]$(C_RESET) $(C_DIM)Linking $(words $(OBJ)) objects...$(C_RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(call progress)

clean:
	@printf "  $(C_RED)$(C_BOLD)[CLN]$(C_RESET) $(C_DIM)Removing object files...$(C_RESET)\n"
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1
	@printf "  $(C_GREEN)$(C_BOLD)[CLN]$(C_RESET) Objects cleaned\n"

fclean: clean
	@printf "  $(C_RED)$(C_BOLD)[CLN]$(C_RESET) $(C_DIM)Removing binary...$(C_RESET)\n"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@printf "  $(C_GREEN)$(C_BOLD)[CLN]$(C_RESET) Full clean done\n"

re: fclean all

info:
	@echo ""
	@printf "  $(C_CYAN)$(C_BOLD)NyxShell Project Info$(C_RESET)\n"
	@printf "  $(C_DIM)─────────────────────────────────$(C_RESET)\n"
	@printf "  $(C_YELLOW)Compiler:$(C_RESET)    $(CC)\n"
	@printf "  $(C_YELLOW)Flags:$(C_RESET)       $(CFLAGS)\n"
	@printf "  $(C_YELLOW)Sources:$(C_RESET)     $(words $(ALL_SRC)) files\n"
	@printf "  $(C_YELLOW)Binary:$(C_RESET)      $(NAME)\n"
	@echo ""

norm:
	@printf "  $(C_MAGENTA)$(C_BOLD)[NORM]$(C_RESET) $(C_DIM)Running norminette...$(C_RESET)\n"
	@norminette $(ALL_SRC) $(SRC_DIR)/including/*.h 2>/dev/null && \
		printf "  $(C_GREEN)$(C_BOLD)[NORM]$(C_RESET) All files OK\n" || \
		printf "  $(C_RED)$(C_BOLD)[NORM]$(C_RESET) Errors found\n"

leak: all
	@printf "  $(C_YELLOW)$(C_BOLD)[MEM]$(C_RESET) $(C_DIM)Running with valgrind...$(C_RESET)\n"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re header info norm leak
