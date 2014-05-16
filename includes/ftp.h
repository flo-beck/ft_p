/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 12:33:28 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/16 12:35:07 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_H
# define FTP_H

#include <stdio.h> /* TAKE OUT!!!!!! */

# define BS					1024
# define NUM_CMDS			2
# define QUIT				"Quit received, closing socket"

typedef struct 		s_e t_e;

typedef struct		s_cmd
{
	char			*name;
	char			*(*fn)(t_e *);
}					t_cmd;

struct				s_e
{
	int				port;
	int				sock;
	int				quit;
	t_cmd			*cmds;
};

/*
**	srcs_serv
*/
int						create_server(int port);
void					ft_accept_client(t_e *e);
t_cmd					*ft_get_cmds(void);
void					ft_read_client(t_e *e, int cs);
char					*ft_ls(t_e *e);
char					*ft_quit(t_e *e);

/*
**	srcs_clie
*/

#endif
