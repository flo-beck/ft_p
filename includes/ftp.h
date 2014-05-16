/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 12:33:28 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/16 20:27:43 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_H
# define FTP_H

#include <stdio.h> /* TAKE OUT!!!!!! */

# define BS					1024
# define NUM_CMDS			6
# define MAXPATHLEN			4096

# define LS					"100"
# define QUIT				"200"
# define CD					"300"
# define GET				"400"
# define PUT				"500"
# define PWD				"600"

typedef struct 		s_e t_e;

typedef struct		s_cmd
{
	char			*(*fn)(t_e *, char *);
}					t_cmd;

struct				s_e
{
	int				port;
	int				sock;
	int				quit;
	/*char			*(*cmds)(t_e *, char *);*/
	t_cmd			*cmds;
	char			*serv_root;
	char			*curr_pwd;
	int				depth;
};

/*
**	srcs_serv
*/
int						create_server(int port);
void					ft_accept_client(t_e *e);
t_cmd					*ft_get_cmds(void);
/*char					(*ft_get_cmds(void))(t_e *, char *);*/
void					ft_read_client(t_e *e, int cs);
char					*ft_ls(t_e *e, char *buf);
char					*ft_quit(t_e *e, char *buf);
char					*ft_cd(t_e *e, char *buf);
char					*ft_put(t_e *e, char *buf);
char					*ft_get(t_e *e, char *buf);
char					*ft_pwd(t_e *e, char *buf);

/*
**	srcs_clie
*/

#endif
