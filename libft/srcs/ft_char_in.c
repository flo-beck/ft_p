/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 12:12:25 by fbeck             #+#    #+#             */
/*   Updated: 2014/01/23 12:13:22 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_char_in(char c, char *list)
{
	if (list)
	{
		while (*list)
		{
			if (*list == c)
				return (1);
			++list;
		}
	}
	return (0);
}
