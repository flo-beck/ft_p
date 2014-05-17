# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbeck <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 12:38:40 by fbeck             #+#    #+#              #
#    Updated: 2014/05/17 19:52:42 by fbeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S				= server
NAME_C				= client
CC					= gcc
FLAGS				= -Wall -Werror -Wextra -pedantic
INCS				= -I ./includes -I ./libft/includes
LIBS				= -L ./libft/ -lft

MAKE				= /usr/bin/make

DIR_SER				= srcs_serv
DIR_CLI				= srcs_clie

SRC_SER				= srcs_serv/ft_server.c \
					  srcs_serv/ft_accept_client.c \
					  srcs_serv/ft_ls.c \
					  srcs_serv/ft_quit.c \
					  srcs_serv/ft_cd.c \
					  srcs_serv/ft_put.c \
					  srcs_serv/ft_get.c \
					  srcs_serv/ft_pwd.c \

SRC_CLI				= srcs_clie/ft_client.c \
					  srcs_clie/ft_send_get.c \
					  srcs_clie/ft_send_put.c \

DIR_OBJ				= .obj
DIR_LIST			= srcs_serv srcs_clie
DIR_INC				= includes

OBJ_S				= $(addprefix $(DIR_OBJ)/, $(SRC_SER:.c=.o))
OBJ_C				= $(addprefix $(DIR_OBJ)/, $(SRC_CLI:.c=.o))

$(addprefix $(DIR_OBJ)/, %.o): %.c $(DIR_INC)
	$(CC) $(FLAG) $(INCS) -o $@ -c $<

all: libft server client

libft:
	$(MAKE) -C libft

$(NAME_S): $(DIR_OBJ) $(OBJ_S)
	$(CC) $(FLAGS) $(OBJ_S) $(LIBS) -o $(NAME_S)

$(NAME_C): $(DIR_OBJ) $(OBJ_C)
	$(CC) $(FLAGS) $(OBJ_C) $(LIBS) -o $(NAME_C)

$(DIR_OBJ) :
	/bin/mkdir $(DIR_OBJ); \
		for DIR in $(DIR_LIST); \
		do \
		/bin/mkdir $(DIR_OBJ)/$$DIR; \
		done

clean:
	$(MAKE) -C libft $@
	/bin/rm -rf $(DIR_OBJ);

fclean: clean
	$(MAKE) -C libft $@
	/bin/rm -rf $(NAME_S) $(NAME_C);

re: fclean all

.PHONY: clean fclean re debug libft server client
