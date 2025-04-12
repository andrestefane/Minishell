# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 17:31:38 by astefane          #+#    #+#              #
#    Updated: 2025/04/12 17:32:41 by astefane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = \
ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar.c \
ft_putendl.c \
ft_putnbr.c \
ft_putstr.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strcmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiler.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c \
get_next_line.c \
get_next_line_utils.c \
ft_strndup.c \
Pipex/More_utils.c \
Pipex/pipex_utils.c \
Pipex/pipex.c \
Pipex/Freedom_errors.c \

OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

TOTAL_FILES := $(words $(SRCS))
COUNT = 0

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\033[1;33mLeaving Libft...\033[0m"

%.o: %.c
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	$(eval PERCENT=$(shell echo $$(( $(COUNT) * 100 / $(TOTAL_FILES) ))))
	@echo "\033[1;32m[ $(PERCENT)%] Building C object $@\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;33mCleaning all .o files...\033[0m"
	@$(RM) $(OBJS) > /dev/null 2>&1

fclean: clean
	@$(RM) $(NAME) > /dev/null 2>&1

re: fclean $(NAME)

bonus: $(OBJS)
	@ar rcs $(NAME) $(OBJS)

.PHONY: all clean fclean re bonus