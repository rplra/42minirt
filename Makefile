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
CFLAGS = -Wall -Wextra -Werror -Iinc -I$(MLX_DIR) #-g3 -fsanitize=address
RM = rm -rf

# OS
OS := $(shell uname -s)

ifeq ($(OS),Darwin)
	MACOS_VER := $(shell sw_vers -productVersion | cut -d. -f1-2)
	CFLAGS += 	-DMAC
	ifeq ($(MACOS_VER), 11.6)
		MLX_DIR = 	mlx/macos2
		MLX 	= 	$(MLX_DIR)/libmlx_intel-mac.a
		LINKS 	= 	$(MLX) -L/usr/X11/lib -lX11 -lXext -framework OpenGL -framework AppKit
	else
		MLX_DIR = 	mlx/macos
		MLX 	= 	$(MLX_DIR)/libmlx.a
		LINKS 	= 	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
	endif
else ifeq ($(OS),Linux)
	CFLAGS += 	-DLINUX
	MLX_DIR = 	mlx/linux
	MLX 	= 	$(MLX_DIR)/libmlx.a
	LINKS 	= 	-L$(MLX_DIR) -lmlx -lGL -lX11 -lXext -lm
else
	$(error Unsupported OS: $(OS))
endif

# Directory
LIB_DIR 	= 	lib
SRC_DIR		= 	src
OBJ_DIR		= 	obj
MAIN_DIR    = 	$(SRC_DIR)/main
PARSE_DIR   = 	$(SRC_DIR)/parse
BVH_DIR     = 	$(SRC_DIR)/bvh
GFX_DIR    	= 	$(SRC_DIR)/gfx
RENDER_DIR  = 	$(SRC_DIR)/render
KEY_DIR     = 	$(SRC_DIR)/key
UTILS_DIR   = 	$(SRC_DIR)/utils

# Files
MAIN_FILES 	= \
	main

PARSE_FILES	= \
	parse_debug parse_error parse_file parse_obj_assign \
	parse_obj_geometry parse_obj parse_scn parse_setup parse_utils

BVH_FILES	= \
	bvh_aabb bvh_aabb2 bvh_aabb3 bvh_init bvh_range \
	bvh_sort_utils bvh_sort bvh_transform_utils bvh_transform bvh_utils

GFX_FILES	= \
	gfx_color gfx_draw gfx_image gfx_init gfx_menu

RENDER_FILES = \
	render_debug render_hit_bvh render_hit_cy render_hit_cy2 render_hit_cy3 \
	render_hit_pl render_hit_sp render_hit render_init_setup render_init \
	render_normal render_rand render_rand2 render_ray_mat render_ray_sample \
	render_ray render_rotate render_utils

KEY_FILES	= \
	key_animate key_close key_config key_debug key_event key_info_utils \
	key_info key_rotation key_scale key_selection key_translate \
	key_utils key_ux

UTILS_FILES	= \
	error free_img free


OBJ 		+= 	$(addprefix $(OBJ_DIR)/main/, $(addsuffix .o, $(MAIN_FILES)))
OBJ 		+= 	$(addprefix $(OBJ_DIR)/parse/, $(addsuffix .o, $(PARSE_FILES)))
OBJ 		+= 	$(addprefix $(OBJ_DIR)/bvh/, $(addsuffix .o, $(BVH_FILES)))
OBJ 		+= 	$(addprefix $(OBJ_DIR)/gfx/, $(addsuffix .o, $(GFX_FILES)))
OBJ 		+= 	$(addprefix $(OBJ_DIR)/render/, $(addsuffix .o, $(RENDER_FILES)))
OBJ 		+= 	$(addprefix $(OBJ_DIR)/key/, $(addsuffix .o, $(KEY_FILES)))
OBJ 		+= 	$(addprefix $(OBJ_DIR)/utils/, $(addsuffix .o, $(UTILS_FILES)))

all : $(NAME)

$(NAME): $(MLX) $(LIB_DIR)/libft.a $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -lft $(LINKS) -o $(NAME)
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
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_output.txt ./$(NAME) $(ARGS)

leaks:
	leaks -atExit -- ./$(NAME) $(ARGS)

.PHONY: all clean fclean re valgrind leaks


# make valgrind ARGS=scn/basics.rt
