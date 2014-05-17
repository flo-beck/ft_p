/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 15:56:20 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/17 20:31:58 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

int						ft_receive(int sock, char *buf, size_t size)
{
	size_t				res;

	res = recv(sock, buf, size, 0);
	if (!ft_strncmp(buf, ERROR, CODE_LEN))
	{
		ft_putstr_fd("ERROR", 2);
		if (buf[CODE_LEN] && !ft_strcmp(&buf[CODE_LEN], NO_FILE))
			ft_putendl_fd(": No such file, or permission denied", 2);
		else if (buf[CODE_LEN] && !ft_strcmp(&buf[CODE_LEN], NO_MAP))
			ft_putendl_fd(": Server failed to map file", 2);
		else
			ft_putendl_fd(" ", 2);
		return (-1);
	}
	return (0);
}

int						ft_create_file(char *code)
{
	char				*name;
	int					fd;

	name = &code[CODE_LEN];
	printf("filename [%s]\n",name );
	if (!name)
		return (-1);
	fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0666);
	return (fd);
}

void					ft_send_get(char *code, int sock)
{
	char				buf[BS + 1];
	size_t				size;
	char				*receive;
	char				*msg;
	int					nf;

	ft_bzero(buf, BS + 1);
	printf("code is [%s]\n",code );
	send(sock, code, ft_strlen(code), 0);
	if (ft_receive(sock, buf, BS) == -1)
		return ;
/*	recv(sock, buf, BS, 0);*/
	printf("recv [%s]\n", buf );
	if (!ft_strncmp(GET_SIZE, buf, CODE_LEN))
	{
		if (!buf[CODE_LEN])
		{
			printf("error didnt receive len\n");
			send(sock, ft_strdup(ERROR), ft_strlen(ERROR), 0);
			return ;
		}
		size = ft_atoi(&buf[CODE_LEN]);
		printf("size %d\n",size );
		nf = ft_create_file(code);
		receive = (char *)malloc(sizeof(char) * (size + 1));
		if (!receive || nf < 0 )
		{
			printf("Cannot receive - too large or already exists\n");
			if (receive)
				free(receive);
			if (nf > 0)
				close(nf);
			send(sock, ft_strdup(ERROR), ft_strlen(ERROR), 0);
			return ;
		}
		else
		{
			/*usleep(10000000);*/
			printf("JUST BEFORE SEND\n");
			send(sock, OK, ft_strlen(OK), 0);
			/*printf("NUMBER OF BYTES SENT %d\n", flo );*/
		}
		printf("send OK\n");
		if (ft_receive(sock, receive, size) == -1)
			return;
		/*recv(sock, receive, size, 0);*/
		ft_bzero(buf, BS + 1);
		printf("RECEIVED : [%s]\n", receive);
		/*if (-1 == write(nf, receive, size))
			send(sock, ERROR, ft_strlen(ERROR), 0);
		else*/
		write(nf, receive, size);
		send(sock, OK, ft_strlen(OK), 0);
		if (ft_receive(sock, buf, BS) == -1)
			return ;
		/*recv(sock, buf, BS, 0);*/
		printf("Finale msg %ss\n",buf );
		free(receive);
		close(nf);
	}
	else
		printf("ERROR: file does not exist\n");
}
