/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 15:56:20 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 21:43:46 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

/*
SEND REQUEST
RECEIVE SIZE /ERR
PREPARE NF AND MALLOC BUF
SEND OK
RECEIVE FILE
WRITE FILE
SEND OK
RECEIVE OK
*/

int						ft_receive_ok(int sock, char *buf, size_t size)
{
	size_t				res;

	res = recv(sock, buf, size, 0);
	if (!ft_strncmp(buf, ERROR, CODE_LEN))
	{
		ft_putstr("ERROR");
		if (buf[CODE_LEN] && !ft_strcmp(&buf[CODE_LEN], NO_FILE))
			ft_putendl(": No such file, or permission denied");
		else if (buf[CODE_LEN] && !ft_strcmp(&buf[CODE_LEN], NO_MAP))
			ft_putendl(": Server failed to map file");
		else
			ft_putendl(" ");
		return (-1);
	}
	return (0);
}

int						ft_create_file(char *code)
{
	char				*name;
	int					fd;

	name = &code[CODE_LEN];
	if (!name)
		return (-1);
	fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0666);
	return (fd);
}

int						ft_check_ok(int sock, char *receive, int nf)
{
	if (!receive || nf < 0 )
	{
		if (receive)
		{
			ft_putendl("ERROR: File already exists");
			free(receive);
		}
		if (nf > 0)
		{
			ft_putendl("ERROR: File too large, malloc failed");
			close(nf);
		}
		send(sock, ERROR, ft_strlen(ERROR), 0);
		return (0);
	}
	return (1);
}

int						ft_prepare(char *code, int sock, char * buf, t_nf *new)
{
	if (!buf[CODE_LEN])
	{
		send(sock, ft_strdup(ERROR), ft_strlen(ERROR), 0);
		ft_putendl("ERROR: Did not receive size of file");
		return (-1);
	}
	new->size = ft_atoi(&buf[CODE_LEN]);
	new->fd = ft_create_file(code);
	new->receive = (char *)malloc(sizeof(char) * (new->size + 1));
	if (ft_check_ok(sock, new->receive, new->fd) == 0)
	{
		send(sock, ERROR, ft_strlen(ERROR), 0);
		return (-1);
	}
	send(sock, OK, ft_strlen(OK), 0);
	return (0);
}

void					ft_send_get(char *code, int sock)
{
	char				buf[BS + 1];
	t_nf				new;

	ft_bzero(buf, BS + 1);
	send(sock, code, ft_strlen(code), 0);
	if (ft_receive_ok(sock, buf, BS) == -1)
		return ;
	if (ft_prepare(code, sock, buf, &new) < 0)
		return ;
	if (ft_receive_ok(sock, new.receive, new.size) == -1)
		return ;
	if (write(new.fd, new.receive, new.size) == new.size)
		ft_putendl("SUCCESS: Get completed");
	else
		ft_putendl("ERROR: Get incomplete");
	ft_bzero(buf, BS + 1);
	send(sock, OK, ft_strlen(OK), 0);
	if (ft_receive_ok(sock, buf, BS) == -1)
		return ;
	free(new.receive);
	close(new.fd);
}
