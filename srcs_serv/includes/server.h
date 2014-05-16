/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 12:06:48 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/15 17:53:51 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_H
# define SERVER_H

#include <stdio.h> /* TAKE OUT!!!!!! */

# define BS				1024
# define NUM_CMDS		2

typedef struct		s_cmd
{
	char			*name;
	char			*(*fn)(void);
}					t_cmd;

int						create_server(int port);
void					ft_accept_client(int my_sock);
void					ft_read_client(int cs);
char					*ft_ls(void);
char					*ft_quit(void);
#endif
