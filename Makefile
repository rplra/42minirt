CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iinclude #-g3 -fsanitize=address
LFLAGS = -lreadline
RM = rm -rf

NAME = miniRT

# Directory
LIBFT_DIR = ./libft
#OBJ_DIR = ./obj/
#MAIN_DIR = ./main/
#PARSING_DIR = ./parsing/

# OS
OS := $(shell uname -s)
ifeq ($(OS),Darwin)
	CFLAGS += -DMAC
	MLX_DIR = mlx/
	MLX = $(MLX_DIR)libmlx.a
	LINKS = -L./mlx -lmlx -L./lib -lft -framework OpenGL -framework AppKit -lm
else ifeq ($(OS),Linux)
	CFLAGS += -DLINUX
	MLX_DIR = minilibx-linux/
	MLX = $(MLX_DIR)libmlx.a
	LINKS = -L$(MLX_DIR) -lmlx -L./lib -lft -lGL -lX11 -lXext -lm
else
	$(error Unsupported OS: $(OS))
endif


# Files
#MAIN_FILES =
#PARSING_FILES =

# Object Files
#OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(MAIN_FILES)))
#OBJ += $(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSING_FILES)))

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	@$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_DIR) -lft $(LFLAGS)
	@echo $(YELLOW) "MiniRT GO!" $(RESET)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

@$(OBJ_DIR)%.o: $(MAIN_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@make -s -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@make -s clean -C $(LIBFT_DIR)
	@echo $(YELLOW) "Cleaned!" $(RESET)

fclean: clean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@make -s fclean -C $(LIBFT_DIR)

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re