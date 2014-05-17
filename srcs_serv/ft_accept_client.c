/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_accept_client.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 11:14:27 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/17 20:36:04 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ftp.h"

t_cmd					*ft_get_cmds(void)
{
	t_cmd				*cmds = NULL;

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

void					ft_read_client(t_e *e, int cs)
{
	int					r;
	char				buf[BS + 1];
	int					i;
	char				*res;
	int					cmd_num;

	while ((r = read(cs, buf, BS)) > 0 && !e->quit)
	{
		buf[r] = '\0';
		printf("buf received %s\n",buf );
		i = 0;
		cmd_num = (buf[0] - '0') - 1;
		printf("CMD_NUM %d\n",cmd_num );
		if (cmd_num < NUM_CMDS)
		{
			printf("executing %d \n", cmd_num );
			res = (e->cmds[cmd_num]).fn(e, buf);
			if ((res))
				send(cs, res, ft_strlen(res), 0);
			else
			{
				printf("THE PREVIOUS COMMAND FAILED OR WAS STOPPED\n");
				/*send(cs, "888\0", 4, 0);*/
			}
		}
		else
		{
			printf("Command not found\n");
			send(cs, "999\0", 4, 0);
		}
		ft_bzero(buf, BS + 1);
	}
	printf("FINISHED READ OR RECEIVED QUIT - I.E. OUT OF WHILE\n");
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
	if (pid == 0) /*fils*/
	{
		e->cs = client_socket;
		ft_read_client(e, client_socket);
		close(client_socket);
	}
	else /*pere*/
		ft_accept_client(e);
}
