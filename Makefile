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
	@echo "Ｌｏａｄｉｎｇ Ｐｒｅｔｔｙ Ｌｉｔｔｌｅ Ｓｈｅｌｌ"
	@$(MAKE) -s progreso
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
	@printf "\033[38;2;252;255;166m                     done \n\033[0m"

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

fclean:
	@$(RM) $(NAME) $(OBJ)
	@printf "\033[38;5;250mfully cleaned 🗑️\n\033[0m"

re: fclean all

.PHONY: clean fclean all re
