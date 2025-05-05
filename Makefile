NAME = minishell
SRC = src/main.c \
	  src/handle_errors.c \
	  src/handle_signals.c \
      src/print_header.c \
	  src/shell/shell_loop.c \
	  src/shell/init_shell.c \
	  src/prompt/process_prompt.c \
	  src/token/piped_tk.c \
	  src/token/tokenizing.c \
	  src/token/token_utils.c \
	  src/token/join_quotes.c \
	  src/exec/env_value.c \
	  src/parser/parse_cmd.c \
	  src/free/free.c \
	  src/free/free_two.c \
	  src/exec/exec.c \
	  src/exec/exec_simple_cmd.c \
	  src/exec/exec_pipeline.c \
	  src/built_ins/check_builtins.c \
	  src/built_ins/builtins_one.c \
	  src/built_ins/builtins_two.c \
	  src/built_ins/builtin_echo.c \
	  src/exec/exec_utils.c \
	  src/exec/redirections.c \
	  src/exec/expand_var.c \
	  src/exec/exec_error.c \
	  src/exec/expand_var_utils.c \
	  src/token/printfs_borrar.c \
	  src/get_next_line/get_next_line.c \
	  src/get_next_line/get_next_line_utils.c \
	  
OBJDIR = objs
OBJ = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g -fsanitize=address

BABY_BLUE = \033[38;2;177;240;247m
RESET = \033[0m
MAKE = make --no-print-directory
INCLUDES = minishell.h
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

$(OBJDIR)/%.o: src/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/shell
	@mkdir -p $(OBJDIR)/prompt
	@mkdir -p $(OBJDIR)/token
	@mkdir -p $(OBJDIR)/parser
	@mkdir -p $(OBJDIR)/exec
	@mkdir -p $(OBJDIR)/free
	@mkdir -p $(OBJDIR)/built_ins
	@mkdir -p $(OBJDIR)/get_next_line
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@printf "\033[38;5;147m"
	@echo "Ｌｏａｄｉｎｇ Ｐｒｅｔｔｙ Ｌｉｔｔｌｅ Ｓｈｅｌｌ"
	@$(MAKE) -s progreso
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@printf "$(BABY_BLUE)                     done \n\033[0m"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

progreso:
	@echo -n ""
	@i=1; \
	while [ $$i -le 10 ]; do \
		echo -n "█████"; \
		sleep 0.15; \
		i=`expr $$i + 1`; \
	done
	@echo ""

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@printf "\033[38;5;250mcleaned 🗑️\n\033[0m"
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean:
	@$(RM) $(NAME) $(OBJ)
	@printf "\033[38;5;250mfully cleaned 🗑️\n\033[0m"
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1

re: fclean all

.PHONY: clean fclean all re progreso