/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 19:16:40 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 22:42:38 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include "ftp.h"

static void				ft_error_msg(char *msg)
{
	ft_putendl(msg);
}

static char				*ft_transfer(int sock, char *file, size_t size)
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

static void				ft_send_file(int sock, char *file, t_nf *new)
{
	char				buf[BS + 1];

	ft_bzero(buf, BS + 1);
	ft_transfer(sock, file, new->size);
	recv(sock, buf, new->size, 0);
	if (ft_strncmp(buf, OK, CODE_LEN))
		ft_putendl("ERROR: PUT incomplete");
	else
		ft_putendl("SUCCESS: PUT completed");
}

void					ft_send_put(char *code, int sock)
{
	t_nf				new;
	STAT				stat;
	char				*file;
	char				buf[BS + 1];

	new.name = &code[CODE_LEN];
	if ((new.fd = open(new.name, O_RDONLY)) < 0)
		return (ft_error_msg("ERROR: No such file, or permission denied"));
	fstat(new.fd, &stat);
	new.size = stat.st_size;
	code = ft_strjoin(code, ft_strjoin(" ", ft_itoa(new.size)));
	ft_bzero(buf, BS + 1);
	send(sock, code, ft_strlen(code), 0);
	recv(sock, buf, new.size, 0);
	if (ft_strncmp(buf, OK, CODE_LEN))
		return (ft_error_msg("ERROR: File too large or already exists"));
	if ((file = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, new.fd, 0))
			!= MAP_FAILED)
		ft_send_file(sock, file, &new);
	else
		ft_send_error(sock, NO_MAP);
}
