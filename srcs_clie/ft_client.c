/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 12:04:11 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 22:22:58 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

static int				usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" [address] [port]", 2);
	return (-1);
}

char					*ft_get_code(char *line, int sock)
{
	if (!ft_strcmp(line, "ls"))
		return (ft_strdup(LS));
	else if (!ft_strcmp(line, "quit"))
		return (ft_strdup(QUIT));
	else if (!ft_strcmp(line, "pwd"))
		return (ft_strdup(PWD));
	else if (!ft_strncmp(line, "cd ", 3) && ft_strlen(line) > 3)
		return (ft_strjoin(CD, &line[3]));
	else if (!ft_strncmp(line, "get ", 4) && ft_strlen(line) > 4)
	{
		ft_send_get(ft_strjoin(GET, &line[4]), sock);
		return (ft_strdup("DONE"));
	}
	else if (!ft_strncmp(line, "put ", 4) && ft_strlen(line) > 4)
	{
		ft_send_put(ft_strjoin(PUT, &line[4]), sock);
		return (ft_strdup("DONE"));
	}
	return (NULL);
}

int						create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (-1 == (connect(sock, (const struct sockaddr *)&sin, sizeof(sin))))
	{
		ft_putendl_fd("Failed to connect to socket", 2);
		return (-1);
	}
	return (sock);
}

static int				ft_treat_line(char *line, int sock)
{
	char				*code;
	char				buf[BS + 1];

	code = ft_get_code(line, sock);
	if (code)
	{
		ft_bzero(buf, BS + 1);
		if (ft_strcmp(code, "DONE"))
		{
			send(sock, code, ft_strlen(code), 0);
			recv(sock, buf, BS, 0);
			buf[BS] = '\0';
			ft_putendl(buf);
			if (!strncmp(buf, QUIT_MSG, 3))
				return (0);
		}
		free(code);
		return (1);
	}
	ft_putstr("Unkown command: ");
	ft_putendl(line);
	return (1);
}

int						main(int ac, char **av)
{
	int					port;
	int					sock;
	char				*line;

	if (ac != 3)
		return (usage(av[0]));
	ft_putendl("Initialising CLIENT");
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	ft_putstr("client > ");
	while ((get_next_line(0, &line) > 0))
	{
		if (ft_treat_line(line, sock) == 0)
			break ;
		free(line);
		ft_putstr("$client > ");
	}
	free(line);
	close(sock);
	return (0);
}
