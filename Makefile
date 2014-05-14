# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbeck <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 12:38:40 by fbeck             #+#    #+#              #
#    Updated: 2014/05/14 11:13:11 by fbeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC                 = clang
FLAG               = -Wall -Werror -Wextra -pedantic
INCS               = -I ./includes -I ./libft/includes
LIBS               = -L ./libft/ -lft

MAKE               = /usr/bin/make

DIR_SER            = srcs_serv
DIR_CLI            = srcs_clie

all: libft
	$(MAKE) -C $(DIR_SER)
#	@/bin/rm -f server
#	@/bin/ln -s $(DIR_SER)/server .
	$(MAKE) -C $(DIR_CLI)
#	@/bin/rm -f client
#	@/bin/ln -s $(DIR_CLI)/client .

libft:
	$(MAKE) -C libft

server:
	$(MAKE) -C $(DIR_SER)
#	@/bin/rm -f server
#	@/bin/ln -s $(DIR_SER)/server .

client:
	$(MAKE) -C $(DIR_CLI)
#	@/bin/rm -f client
#	@/bin/ln -s $(DIR_CLI)/client .

clean:
	$(MAKE) -C libft $@
	$(MAKE) -C $(DIR_SER) $@
	$(MAKE) -C $(DIR_CLI) $@

fclean: clean
	$(MAKE) -C libft $@
	$(MAKE) -C $(DIR_SER) $@
	$(MAKE) -C $(DIR_CLI) $@

re: fclean all

.PHONY: clean fclean re debug libft server client
