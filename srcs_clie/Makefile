# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbeck <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 12:38:40 by fbeck             #+#    #+#              #
#    Updated: 2014/05/16 12:32:56 by fbeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= ../client

CC					= gcc
FLAG				= -Wall -Werror -Wextra -pedantic
INCS				= -I ../includes -I ../libft/includes
LIBS				= -L ../libft/ -lft

SRC					= srcs/ft_client.c \

DIR_SRC				= srcs
DIR_INC				= includes
DIR_OBJ				= .obj

DIR_LIST			= srcs

OBJ					= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))

all: libft $(NAME)

libft:
	$(MAKE) -C ../libft

$(addprefix $(DIR_OBJ)/, %.o): %.c $(DIR_INC)
	$(CC) $(FLAG) $(INCS) -o $@ -c $<

$(NAME): $(DIR_OBJ) $(OBJ)
	$(CC) $(FLAG) $(OBJ) $(LIBS) -o $(NAME)

$(DIR_OBJ) :
	/bin/mkdir $(DIR_OBJ); \
		for DIR in $(DIR_LIST); \
		do \
		/bin/mkdir $(DIR_OBJ)/$$DIR; \
		done

clean:
	$(MAKE) -C ../libft $@
	/bin/rm -rf $(DIR_OBJ);

fclean: clean
	$(MAKE) -C ../libft $@
	/bin/rm -rf $(NAME);

re: fclean all

debug : FLAG += -g3 -fno-inline -DD_ERRORS_ON
debug : re

.PHONY: clean fclean re debug libft
