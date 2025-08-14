# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 11:26:39 by rraja-az          #+#    #+#              #
#    Updated: 2025/08/14 16:14:35 by rraja-az         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

# Project
NAME = libft.a

# Directory
SRC_DIRS = ftc lst gnl quaternion
OBJ_DIR  = obj

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Compiler and tools
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinc/
AR      = ar
ARFLAGS = rcs
RM      = rm -f

# Targets
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "Compile $(NAME)		: OK!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "Clean $(NAME)		: OK!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Full Clean $(NAME)	: OK!"

re: fclean all

.PHONY: all clean fclean re