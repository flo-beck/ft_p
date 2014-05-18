/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 18:46:04 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 22:47:25 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

int						ft_receive_ok(int sock, char *buf, size_t size)
{
	size_t				res;

	res = recv(sock, buf, size, 0);
	if (!ft_strncmp(buf, ERROR, CODE_LEN))
	{
		ft_putstr_fd("[ERROR", 2);
		if (buf[CODE_LEN] && !ft_strcmp(&buf[CODE_LEN], NO_FILE))
			ft_putendl_fd(": No such file, or permission denied	]", 2);
		else if (buf[CODE_LEN] && !ft_strcmp(&buf[CODE_LEN], NO_MAP))
			ft_putendl_fd(": Server failed to map file		]", 2);
		else
			ft_putendl_fd(" ", 2);
		return (-1);
	}
	return (0);
}

int						ft_create_file(char *name)
{
	int					fd;

	if (!name)
		return (-1);
	fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0666);
	return (fd);
}

int						ft_check_ok(int sock, char *receive, int nf)
{
	if (!receive || nf < 0)
	{
		if (receive)
		{
			ft_putendl("[ERROR: File already exists		]");
			free(receive);
		}
		if (nf > 0)
		{
			ft_putendl("[ERROR: File too large, malloc failed	]");
			close(nf);
		}
		return (0);
	}
	return (1);
}

int						ft_prepare(int sock, char *buf, t_nf *new)
{
	char				**split;

	if (!buf[CODE_LEN])
	{
		ft_putendl("[ERROR: Did not receive file info	]");
		return (-1);
	}
	split = ft_strsplit(&buf[CODE_LEN], ' ');
	new->size = ft_atoi(split[1]);
	new->name = ft_strdup(split[0]);
	ft_free_split(&split);
	new->fd = ft_create_file(new->name);
	new->receive = (char *)malloc(sizeof(char) * (new->size + 1));
	if (ft_check_ok(sock, new->receive, new->fd) == 0)
		return (-1);
	send(sock, OK, ft_strlen(OK), 0);
	return (0);
}

char					*ft_put(t_e *e, char *buf)
{
	char				reply[BS + 1];
	t_nf				new;

	if (ft_prepare(e->cs, buf, &new) < 0)
		return (ft_strdup(ERROR));
	if (ft_receive_ok(e->cs, new.receive, new.size) == -1)
		return (NULL);
	if (write(new.fd, new.receive, new.size) == new.size)
		ft_putendl("[SUCCESS: PUT completed			]");
	else
		ft_putendl("[ERROR: PUT incomplete			]");
	send(e->cs, OK, ft_strlen(OK), 0);
	free(new.receive);
	free(new.name);
	close(new.fd);
	return (ft_strdup(OK));
}
