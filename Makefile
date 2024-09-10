# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 09:28:27 by hutzig            #+#    #+#              #
#    Updated: 2024/09/10 09:48:32 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

DIR_LIBFT = ./lib/libft
DIR_SRC = ./sources
DIR_OBJ = $(DIR_SRC)/objects

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -L $(DIR_LIBFT) -lft
RM = rm -rf

SOURCES = main.c \


SRC = $(addprefix $(DIR_SRC)/,$(SOURCES))

OBJECTS = $(patsubst $.c,$(DIR_OBJ)/%.o,$(notdir $(SOURCES)))

HEADERS = -I ./include -I $(DIR_LIBFT)

LIBFT = $(DIR_LIBFT)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(DIR_LIBFT)
	@echo "Libft generared!"

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIBFT_FLAGS) $(HEADERS) -o $@
	@echo "pipex program is generated!"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "Compiling: $<"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean:
	@$(RM) $(DIR_OBJ)
	@make clean -C $(DIR_LIBFT)
	@echo "pipex objects are removed!"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(DIR_LIBFT)
	@echo "All executable files are removed!"

re: fclean all

.PHONY: all clean fclean re
