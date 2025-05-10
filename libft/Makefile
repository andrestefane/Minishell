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
free_split.c \

OBJ_DIR = libft_obj
OBJS = $(SRCS:.c=.o)
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(OBJS))

CC = cc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror

NAME = libft.a

TOTAL_FILES := $(words $(SRCS))
COUNT = 0

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "\033[1;33mLeaving Libft...\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	$(eval PERCENT=$(shell echo $$(( $(COUNT) * 100 / $(TOTAL_FILES) ))))
	@echo "\033[1;32m[ $(PERCENT)%] Building C object $@\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;33mCleaning all .o files...\033[0m"
	@$(RM) $(OBJ_FILES) > /dev/null 2>&1
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re