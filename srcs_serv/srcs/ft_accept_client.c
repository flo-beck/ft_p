/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_accept_client.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 11:14:27 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/14 17:48:38 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "libft.h"
#include "server.h"

static t_cmd			*ft_get_cmds(void)
{
	static t_cmd		*cmds = NULL;

	if (!cmds)
	{
		if (!(cmds = (t_cmd *)malloc(sizeof(t_cmd) * (NUM_CMDS + 1))))
			ft_error("Failed to malloc 'cmds'");
		cmds[NUM_CMDS] = NULL;
		cmds[0].name = "ls";
		cmds[0].fn = &ft_ls;
		cmds[1].name = "quit";
		cmds[1].fn = &ft_quit;
		cmds[2].name = "put";
		cmds[2].fn = &ft_put;
		cmds[3].name = "get";
		cmds[3].fn = &ft_get;
		cmds[4].name = "pwd";
		cmds[4].fn = &ft_pwd;
		cmds[5].name = "cd";
		cmds[5].fn = &ft_cd;
	}
	return (cmds);
}

void					ft_read_client(int cs)
{
	int					r;
	char				buf[BS + 1];
	int					i;
	char				*res;
	t_cmd				*cmds;

	cmds = ft_get_cmds();
	while ((r = read(cs, buf, BS)) > 0)
	{
		buf[r] = '\0';
		i = 0;
		while (cmds[i].name)
		{
			if (!ft_strncmp(buf, cmds[i].name, 4))
			{
				res = cmds[i].ft();
				if ((res))
					send(cs, res, ft_strlen(res), 0);
				/*else
					ft_send("ERROR", res);*/
			}
			i++;
		}
	/*	else
			ft_send("ERROR", buf);*/
		/*ft_putendl(buf);*/
	}
}

void					ft_accept_client(int my_sock)
{
	int					pid;
	int					client_socket;
	struct sockaddr_in	csin;
	unsigned int		cslen;

	client_socket = accept(my_sock, (struct sockaddr *)&csin, &cslen);
	if (-1 == (pid = fork()))
		return ;
	if (pid == 0) /*fils*/
	{
		ft_read_client(client_socket);
		close(client_socket);
	}
	else /*pere*/
		ft_accept_client(my_sock);
}
