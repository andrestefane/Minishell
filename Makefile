CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror 
LIBFT = libft
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
LDFLAGS = -lreadline

OBJ_DIR = obj
SRCS = \
	main.c \
	./Tokenizer/Tokens.c \
	./Tokenizer/tokenizer_utils.c \
	./Tokenizer/type_of_tokens.c \
	./Tokenizer/metachar_utils.c \
	./Tokenizer/quoted_utils.c \
	./Varibles/variables.c \
	./Varibles/Utils_variables.c \
	./Exec/Execute.c \
	./Exec/path_utils.c \
	./Parser/parser.c \
	./Parser/parser_utils.c

# Cambio importante: generamos la ruta de cada .o dentro de obj/ manteniendo subdirectorios
OBJS = $(SRCS:.c=.o)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(OBJS))

NAME = Mini
INCLUDES = -I. -I includes

TOTAL_FILES := $(words $(SRCS))
COUNT = 0

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@echo "\033[1;33mCompiling libft...\033[0m"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJ_FILES) $(LIBFT_LIB)
	@ $(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIBFT_LIB) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@if [ "$(COUNT)" -eq "0" ]; then echo "\033[1;33mCompiling Mini...\033[0m"; fi
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	$(eval PERCENT=$(shell echo $$(( $(COUNT) * 100 / $(TOTAL_FILES) ))))
	@echo "\033[1;32m[ $(PERCENT)%] Building C object $@\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "\033[1;33mCleaning all .o files...\033[0m"
	@rm -rf $(OBJ_DIR) > /dev/null 2>&1
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1

fclean: clean
	@rm -rf $(NAME) > /dev/null 2>&1
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re