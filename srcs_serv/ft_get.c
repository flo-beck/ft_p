/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 18:45:25 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 23:08:08 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ftp.h"

static char				*ft_send_file(int sock, char *file, size_t size)
{
	char				reply[BS + 1];

	ft_bzero(reply, BS);
	send(sock, file, size, 0);
	recv(sock, reply, BS, 0);
	if (!ft_strcmp(reply, OK))
		return (ft_strdup("SUCCESS: File sent"));
	else
		return (ft_strdup("ERROR: Send failed"));
}

static int				ft_size_ok(int sock, struct stat *stat, int fd)
{
	char				*msg;
	char				reply[BS + 1];
	char				*size;

	ft_bzero(reply, BS);
	fstat(fd, stat);
	size = ft_itoa(stat->st_size);
	msg = ft_strjoin(GET_SIZE, size);
	send(sock, msg, ft_strlen(msg), 0);
	recv(sock, reply, BS, 0);
	free(size);
	free(msg);
	if (!ft_strcmp(reply, OK))
		return (1);
	return (0);
}

static char				*ft_get_name(char *buf)
{
	int					i;

	i = CODE_LEN;
	while (buf[i] != '\0' && ft_isblank(buf[i]))
		i++;
	return (&buf[i]);
}

static void				ft_send_error(int sock, char *code)
{
	char				*msg;

	msg = NULL;
	if (!strcmp(code, NO_MAP))
		ft_error("[ERROR: Failed to map file	]");
	else
		ft_error("[ERROR: Failed to open file		]");
	msg = ft_strjoin(ERROR, code);
	send(sock, msg, ft_strlen(msg), 0);
	free(msg);
}

char					*ft_get(t_e *e, char *buf)
{
	char				*name;
	int					fd;
	char				*msg;
	char				*file;
	STAT				stats;

	name = ft_get_name(buf);
	if ((fd = open(name, O_RDONLY)) > 0)
	{
		if (ft_size_ok(e->cs, &stats, fd) == 1)
		{
			if ((file = mmap(0, stats.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
					!= MAP_FAILED)
				return (ft_send_file(e->cs, file, stats.st_size));
			else
				ft_send_error(e->cs, NO_MAP);
		}
		else
			ft_error("[ERROR: the client experienced an error	]");
	}
	else
		ft_send_error(e->cs, NO_FILE);
	return (NULL);
}
