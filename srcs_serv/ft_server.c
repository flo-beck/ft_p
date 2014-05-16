/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 12:04:11 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/16 12:36:33 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "libft.h"
#include "ftp.h"

static int				usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" [port]", 2);
	return (-1);
}

static void				ft_init_e(t_e *e)
{
	e->port = 0;
	e->sock = 0;
	e->quit = 0;
	e->cmds = ft_get_cmds();
}

int						create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (-1 == (bind(sock, (const struct sockaddr *)&sin, sizeof(sin))))
	{
		ft_putendl_fd("Failed to bind socket", 2);
		return (-1);
	}
	printf("COUCOU\n");
	listen(sock, 42);
	printf("LISTENED\n");
	return (sock);
}

int							main(int ac, char **av)
{
	t_e						e;

	if (ac != 2)
		return(usage(av[0]));
	ft_init_e(&e);
	ft_putendl("I AM THE AWESOME SERVER.");
	e.port = ft_atoi(av[1]);
	e.sock = create_server(e.port);
	ft_accept_client(&e);
	close(e.sock);
	return (0);
}
