# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 17:34:42 by astefane          #+#    #+#              #
#    Updated: 2025/04/23 04:15:07 by alejaro2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBFT = libft
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
LDFLAGS = -lreadline

SRCS = \
	main.c \
	./Tokenizer/Tokens.c \
	./Tokenizer/tokenizer_utils.c\
	./Exec/Execute.c

OBJS = $(SRCS:.c=.o)
NAME = Mini
INCLUDES = -I. -I includes

TOTAL_FILES := $(words $(SRCS))
COUNT = 0

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@echo "\033[1;33mCompiling libft...\033[0m"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_LIB) $(LDFLAGS)

%.o: %.c
	@if [ "$(COUNT)" -eq "0" ]; then echo "\033[1;33mCompiling So_long...\033[0m"; fi
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	$(eval PERCENT=$(shell echo $$(( $(COUNT) * 100 / $(TOTAL_FILES) ))))
	@echo "\033[1;32m[ $(PERCENT)%] Building C object $@\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "\033[1;33mCleaning all .o files...\033[0m"
	@rm -rf $(OBJS) > /dev/null 2>&1
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1

fclean: clean
	@rm -rf $(NAME) > /dev/null 2>&1
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re