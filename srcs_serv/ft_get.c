/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 18:45:25 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/17 21:01:24 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ftp.h"

/*     int
	   open(const char *path, int oflag, ...);*/

/* int
      fstat(int fildes, struct stat *buf);*/



char					*ft_get(t_e *e, char *buf)
{
	int					i;
	char				*name;
	int					fd;
	int					r;
	struct stat			stat;
	char				*msg;
	char				reply[BS + 1];
	char				*file;

	printf("BUF IS [%s]\n",buf );
	i = CODE_LEN;
	while (buf[i] != '\0' && ft_isblank(buf[i]))
		i++;
	name = &buf[i];
	printf("NAME = %s\n",name );
	if ((fd = open(name, O_RDONLY)) > 0)
	{
		ft_bzero(reply, BS);
		fstat(fd, &stat);
		msg = ft_strjoin(GET_SIZE, ft_itoa((stat.st_size)));
		send(e->cs, msg, ft_strlen(msg), 0);
		printf("SENT FIRST MSG [%s]\n",msg ); // BLOCKING HERE
		printf("WAITING HERE FOR REPLY\n");
		recv(e->cs, reply, BS, 0);
		printf("REPLY [%s]\n",reply );
		if (!ft_strcmp(reply, OK))
		{
			printf("received ok\n");
			if ((file = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
					!= MAP_FAILED)
			{
				ft_bzero(reply, BS);
				send(e->cs, file, stat.st_size, 0);
				recv(e->cs, reply, BS, 0);
				if (!ft_strcmp(reply, OK))
					return (ft_strdup("SUCCESS: File sent"));
				else
					return (ft_strdup("ERROR: Send failed"));
			}
			else
			{
				ft_error("Failed to map file");
				msg = ft_strjoin(ERROR, NO_MAP);
				send(e->cs, msg, ft_strlen(msg), 0);
			}
		}
		else
			ft_error("ERROR: the client experienced an error");
	}
	else
	{
		ft_error("Failed to open file");
		msg = ft_strjoin(ERROR, NO_FILE);
		send(e->cs, msg, ft_strlen(msg), 0);
	}
	return (NULL);
}
