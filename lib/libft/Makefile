# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:51:18 by hutzig            #+#    #+#              #
#    Updated: 2024/08/30 18:22:49 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variable NAME specifies the name of the output file;
NAME = libft.a

# Variable SOURCES contains .c files to be compiled to object files;
SOURCES = ft_atoi.c \
	ft_atof.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_max.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strequ.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_striteri.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \

# Variable to additional source files to be compiled separately;
BONUS_S = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \

# Variable OBJECTS stores the names of the object files generated from the source; 
OBJECTS = $(SOURCES:.c=.o)

# Variable BONUS_O stores the names of .o files generated from bonus sources;
BONUS_O = $(BONUS_S:.c=.o)

# Specifies the required header file for compilation;
HEADER = libft.h

# Variable to specify the compiler command - usually to the default C compiler on the system;
CC = cc

# Compiler flags to enable compiler warnings (treat them as errors);
CFLAGS = -Wall -Wextra -Werror

# Command for removing files;
RM = rm -f

# Command to create a new archivie from .o files (or replace/create/sort);
AR = ar rcs

# Default rule to build the '$(NAME)' target;
all: $(NAME)

# Rule to compile .c (speficied by '$<') into .o files (named specified by -o $@) without linking (-c);
%.o:%.c $(HEADER)
	@$(CC) $(CFLAGS) -c -o $@ $<

# Rule to build the final library archive file;
$(NAME): $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)
	@echo "libft is generated!"

# Rule to build the bonus functions and add them to the library;
bonus: .bonus
	
.bonus: $(NAME) $(BONUS_O)
	@$(AR) $(NAME) $(BONUS_O)
	@touch .bonus

# Rule that removes all object files and bonus object files;
clean:
	@$(RM) $(OBJECTS) $(BONUS_O)
	@$(RM) .bonus
	@echo "libft objects are removed!"

# Target that also removes the executable;
fclean: clean
	@$(RM) $(NAME)
	@$(RM) .bonus
	@echo "libft archive file is removed!"

# Target that cleans and rebuilds ('all') the project;
re:	fclean all

# .PHONY specifies targets that aren't files, preventing conflicts with files of the same name;
.PHONY: all clean fclean re bonus
