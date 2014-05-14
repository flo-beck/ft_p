/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 12:06:48 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/14 12:54:53 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_H
# define SERVER_H

#include <stdio.h> /* TAKE OUT!!!!!! */

# define BS				1024

int						create_server(int port);
void					ft_accept_client(int my_sock);
void					ft_read_client(int cs);
#endif
