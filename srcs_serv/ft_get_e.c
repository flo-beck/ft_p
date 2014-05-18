/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 13:40:52 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 13:51:07 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftp.h"

t_e						*ft_get_e(void)
{
	static t_e			*e = NULL;

	if (!e)
		e = (t_e *)malloc(sizeof(t_e));
	return (e);
}
