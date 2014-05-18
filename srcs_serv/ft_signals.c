/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 13:11:27 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 15:47:27 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "ftp.h"

static void				ft_control_stop(int i)
{
	t_e					*e;

	(void)i;
	e = ft_get_e();
	ft_putstr("\n");
	ft_closedown(e);
	exit (0);
}

void					ft_setup_signal(void)
{
	if ((signal(SIGQUIT, ft_control_stop) == SIG_ERR)
			|| (signal(SIGINT, ft_control_stop) == SIG_ERR))
		exit(-1);
}
