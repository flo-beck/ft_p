/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 19:16:40 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 21:43:20 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include "ftp.h"

static char				*ft_send_file(int sock, char *file, size_t size)
{
	char				reply[BS + 1];

	ft_bzero(reply, BS);
	send(sock, file, size, 0);
	recv(sock, reply, BS, 0);
	if (!ft_strcmp(reply, OK))
		return ("SUCCESS: File sent");
	else
		return ("ERROR: Send failed");
}

static void				ft_send_error(int sock, char *code)
{
	char				*msg;

	msg = NULL;
	if (!strcmp(code, NO_MAP))
		ft_putendl("ERROR: Failed to map file	");
	msg = ft_strjoin(ERROR, code);
	send(sock, msg, ft_strlen(msg), 0);
}

void					ft_send_put(char *code, int sock)
{
	int					fd;
	char				*name;
	size_t				size;
	struct stat			stat;
	char				*file;
	char				buf[BS + 1];


	name = &code[CODE_LEN];
	if ((fd = open(name, O_RDONLY)) < 0)
	{
		ft_putendl("ERROR: No such file, or permission denied");
		return ;
	}
	fstat(fd, &stat);
	code = ft_strjoin(code, ft_strjoin(" ", ft_itoa(stat.st_size)));
	ft_bzero(buf, BS + 1);
	send(sock, code, ft_strlen(code), 0);
	recv(sock, buf, size, 0);
	if (ft_strncmp(buf, OK, CODE_LEN))
	{
		ft_putendl("ERROR: File too large or already exists");
		return ;
	}
	if ((file = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			!= MAP_FAILED)
	{
		ft_bzero(buf, BS + 1);
		ft_send_file(sock, file, stat.st_size);
		recv(sock, buf, size, 0);
		if (ft_strncmp(buf, OK, CODE_LEN))
			ft_putendl("ERROR: PUT incomplete");
		else
			ft_putendl("SUCCESS: PUT completed");
	}
	else
		ft_send_error(sock, NO_MAP);
}
