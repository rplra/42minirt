# Colour
RESET			= \033[0m
BLACK    		= \033[30m		# Black
RED      		= \033[31m		# Red
GREEN    		= \033[32m		# Green
YELLOW   		= \033[33m		# Yellow
BLUE     		= \033[34m		# Blue
MAGENTA  		= \033[35m		# Magenta
CYAN     		= \033[36m		# Cyan
WHITE    		= \033[37m		# White

NAME = miniRT

CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iinc #g3 -fsanitize=address
RM = rm -rf

# OS
OS := $(shell uname -s)
ifeq ($(OS),Darwin)
	CFLAGS += 	-DMAC
	MLX_DIR = 	mlx/macos
	MLX 	= 	$(MLX_DIR)libmlx.a
	LINKS 	= 	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
else ifeq ($(OS),Linux)
	CFLAGS += 	-DLINUX
	MLX_DIR = 	mlx/linux
	MLX 	= 	$(MLX_DIR)libmlx.a
	LINKS 	= 	-L$(MLX_DIR) -lmlx -lGL -lX11 -lXext -lm
else
	$(error Unsupported OS: $(OS))
endif

# Directory
LIB_DIR 	= 	lib
SRC_DIR		= 	src
OBJ_DIR		= 	obj
MAIN_DIR 	= 	$(SRC_DIR)/main
PARSE_DIR 	= 	$(SRC_DIR)/parse
RT_DIR		=	$(SRC_DIR)/raytracing
UTILS_DIR 	= 	$(SRC_DIR)/utils

# Sources
SRCS		=	$(wildcard $(MAIN_DIR)/*.c) \
				$(wildcard $(PARSE_DIR)/*.c) \
				$(wildcard $(RT_DIR)/*.c) \
				$(wildcard $(UTILS_DIR)/*.c)
OBJS		=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all : $(NAME)

$(NAME): $(MLX) $(LIB_DIR)/libft.a $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) -lft $(LINKS) -o $(NAME)
	@echo "Compile $(NAME)		: OK!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/libft.a:
	@make -s -C $(LIB_DIR)

$(MLX):
	@make -C $(MLX_DIR) > /dev/null
	@echo "Compile libmlx.a	: OK!"

clean:
	@$(RM) $(OBJ_DIR)
	@make -s clean -C $(LIB_DIR) > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "Clean $(NAME)		: OK!"

fclean: clean
	@$(RM) $(NAME)
	@make -s fclean -C $(LIB_DIR)
	@echo "Full Clean $(NAME)	: OK!"

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re valgrind