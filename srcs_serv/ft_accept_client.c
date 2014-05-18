/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_accept_client.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 11:14:27 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 22:03:27 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

t_cmd					*ft_get_cmds(void)
{
	static t_cmd		*cmds = NULL;

	if (!cmds)
	{
		if (!(cmds = (t_cmd *)malloc(sizeof(t_cmd) * (NUM_CMDS + 1))))
			return (cmds);
		(cmds[NUM_CMDS]).fn = NULL;
		(cmds[0]).fn = &ft_ls;
		(cmds[1]).fn = &ft_cd;
		(cmds[2]).fn = &ft_get;
		(cmds[3]).fn = &ft_put;
		(cmds[4]).fn = &ft_pwd;
		(cmds[5]).fn = &ft_quit;
	}
	return (cmds);
}

static void				ft_treat_code(t_e *e, char *buf, char *res)
{
	int					i;
	int					cmd_num;
	char				*msg;

	i = 0;
	cmd_num = (buf[0] - '0') - 1;
	if (cmd_num < NUM_CMDS)
	{
		res = (e->cmds[cmd_num]).fn(e, buf);
		if ((res))
		{
			send(e->cs, res, ft_strlen(res), 0);
			free(res);
		}
		else
			ft_putendl("[The previous command failed or was stopped]");
	}
	else
	{
		ft_putendl("[Command not found			]");
		msg = ft_strdup(ERROR);
		send(e->cs, msg, ft_strlen(msg), 0);
		free(msg);
	}
}

void					ft_read_client(t_e *e, int cs)
{
	int					r;
	char				buf[BS + 1];
	char				*res;

	while ((r = read(cs, buf, BS)) > 0 && !e->quit)
	{
		buf[r] = '\0';
		res = NULL;
		if (!strncmp(ERROR, buf, CODE_LEN))
			ft_putendl("[Error message received			]");
		else
		{
			ft_treat_code(e, buf, res);
		}
		ft_bzero(buf, BS + 1);
	}
	ft_putendl("[Closing connection			]");
}

void					ft_accept_client(t_e *e)
{
	int					pid;
	int					client_socket;
	struct sockaddr_in	csin;
	unsigned int		cslen;

	client_socket = accept(e->sock, (struct sockaddr *)&csin, &cslen);
	if (-1 == (pid = fork()))
		return ;
	if (pid == 0)
	{
		e->in_son = 1;
		e->cs = client_socket;
		ft_read_client(e, client_socket);
		close(client_socket);
	}
	else
		ft_accept_client(e);
}
