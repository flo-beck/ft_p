/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <fbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 17:42:41 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 21:37:34 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

char					*ft_quit(t_e *e, char *buf)
{
	(void)buf;
	e->quit = 1;
	return (ft_strdup(QUIT_MSG));
}
