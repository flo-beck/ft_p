/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 12:04:11 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/17 19:12:03 by fbeck            ###   ########.fr       */
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
#include "libft.h"
#include "ftp.h"

static int			usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" [address] [port]", 2);
	return (-1);
}

static void			ft_unknown_cmd(char *line)
{
	ft_putstr("Unkown command: ");
	ft_putendl(line);
}

char				*ft_get_code(char *line, int sock)
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
		return ("DONE");
	}
	else if (!ft_strncmp(line, "put ", 4) && ft_strlen(line) > 4)
	{
		ft_send_put(ft_strjoin(PUT, &line[4]), sock);
		return ("DONE");
	}
	return (NULL);
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
	char				buf[BS + 1];
	char				*code;

	if (ac != 3)
		return(usage(av[0]));
	ft_putendl("I AM THE CLIENT.");
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	ft_putstr("client > ");
	while((get_next_line(0, &line) > 0))
	{
		/*write(sock, line, ft_strlen(line));*/
		code = ft_get_code(line, sock);
		if (code)
		{
			ft_bzero(buf, BS + 1);
			if (ft_strcmp(code, "DONE"))
			{
				send(sock, code, ft_strlen(code), 0);
				free(code);
				recv(sock, buf, BS, 0);
				buf[BS] = '\0';
				ft_putendl(buf);
				if (!strncmp(buf, QUIT, 3))
					break ;
			}
		}
		else
			ft_unknown_cmd(line);
		ft_putstr("client > ");
	}
	close(sock);
	return (0);
}
