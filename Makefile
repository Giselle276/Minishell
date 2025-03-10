NAME = minishell
SRC = main.c \
	  print_header.c

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

FUCHSIA = \033[38;2;237;62;247m
RESET = \033[0m


INCLUDES = minishell.h
%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@printf "\033[38;5;147m"
	@echo "  Ｓｔａｒｔｉｎｇ　ｔｈｅ　ｃｏｍｐｉｌａｔｉｏｎ"
	@$(MAKE) -s progreso
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
	@printf "\033[1;33;213mCompiled ✅\n\033[0m"

progreso:
	@echo -n ""
	@for i in $(shell seq 1 50); do \
		echo -n "█"; \
		sleep 0.1; \
	done
	@echo ""

all: $(NAME)

clean:
	@rm -f $(OBJ)
	@printf "\033[1;36;213mCleaned 🗑️\n\033[0m"

fclean:
	@rm -f $(NAME) $(OBJ)
	@printf "\033[1;34;213mFully cleaned 🗑️🧹\n\033[0m"

re: fclean all

.PHONY: clean fclean all re
