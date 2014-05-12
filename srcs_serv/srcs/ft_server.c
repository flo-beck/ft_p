/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 12:04:11 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/12 19:42:25 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "libft.h"
#include "server.h"

static int			usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" [port]", 2);
	return (-1);
}

int					create_server(int port)
{
	int				sock;
	struct protoent	*proto;
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
	listen(sock, 42);
	return (sock);
}

void					ft_read_client(int cs)
{
	int					r;
	char				buf[1025];

	while ((r = read(cs, buf, 1024)) > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf);
	}
}

int						main(int ac, char **av)
{
	int					port;
	int					sock;
	int					client_socket;
	struct sockaddr_in	csin;
	unsigned int		cslen;

	if (ac != 2)
		return(usage(av[0]));
	ft_putendl("I AM THE AWESOME SERVER.");
	port = ft_atoi(av[1]);
	sock = create_server(port);
	client_socket = accept(sock, (struct sockaddr *)&csin, &cslen);
	ft_read_client(client_socket);
	close(client_socket);
	close(sock);
	return (0);
}
