/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 12:04:11 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/14 17:49:05 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "libft.h"
#include "client.h"

static int			usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" [address] [port]", 2);
	return (-1);
}

int					create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (-1 == (connect(sock, (const struct sockaddr *)&sin, sizeof(sin))))
	{
		ft_putendl_fd("Failed to connect to socket", 2);
		return (-1);
	}
	return (sock);
}

int						main(int ac, char **av)
{
	int					port;
	int					sock;
	char				*line;

	if (ac != 3)
		return(usage(av[0]));
	ft_putendl("I AM THE CLIENT.");
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	while((get_next_line(0, &line) > 0))
		write(sock, line, ft_strlen(line));
	close(sock);
	return (0);
}
