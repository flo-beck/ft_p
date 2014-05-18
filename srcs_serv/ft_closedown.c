/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closedown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 13:25:38 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 22:04:59 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

static void				ft_free_e(t_e **e)
{
	int					i;

	i = 0;
	free((*e)->serv_root);
	free((*e)->curr_pwd);
	free((*e)->cmds);
	free(*e);
}

void					ft_closedown(t_e *e)
{
	if (e->in_son)
		ft_putendl("[Connection closed			]");
	else
		ft_putendl("[Exiting				]");
	if (e->sock != 0)
		close(e->sock);
	if (e->cs != 0)
		close(e->cs);
	ft_free_e(&e);
}
