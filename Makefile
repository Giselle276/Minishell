NAME = minishell
SRC = src/main.c \
	  src/handle_errors.c \
	  src/handle_signals.c \
      src/print_header.c \
	  src/shell/shell_loop.c \
	  src/shell/init_shell.c \
	  src/prompt/process_prompt.c \
	  src/token/tokens.c \
	  
OBJDIR = objs
OBJ = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g

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
	@for i in $(shell seq 1 10); do \
		echo -n "█████"; \
		sleep 0.15; \
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
