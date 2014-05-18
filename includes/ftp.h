/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 12:33:28 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 21:35:22 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_H
# define FTP_H

#include <stdio.h> /* TAKE OUT!!!!!! */
# include "libft.h"

# define BS					1024
# define NUM_CMDS			6
# define MAXPATHLEN			4096
# define CODE_LEN			3

# define LS					"100"
# define CD					"200"
# define GET				"300"
# define GET_SIZE			"301"
# define PUT				"400"
# define PWD				"500"
# define QUIT				"600"
# define QUIT_MSG			"Exiting"
# define OK					"010"
# define ERROR				"090"
# define NO_FILE			"901"
# define NO_MAP				"902"

typedef struct 		s_e t_e;

typedef struct		s_cmd
{
	char			*(*fn)(t_e *, char *);
}					t_cmd;

typedef struct		s_nf
{
	int				fd;
	char			*receive;
	size_t			size;
	char			*name;
}					t_nf;

struct				s_e
{
	int				port;
	int				sock;
	int				quit;
	int				in_son;
	/*char			*(*cmds)(t_e *, char *);*/
	t_cmd			*cmds;
	char			*serv_root;
	char			*curr_pwd;
	int				depth;
	int				cs;
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
void					ft_setup_signal(void);
void					ft_closedown(t_e *e);
t_e						*ft_get_e(void);
int						ft_error(char *msg);

/*
**	srcs_clie
*/
void					ft_send_get(char *code, int sock);
void					ft_send_put(char *code, int sock);

#endif
