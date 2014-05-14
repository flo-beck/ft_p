/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 17:04:25 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/14 17:44:14 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "server.h"

void					ft_del_elem(void *content, size_t size)
{
	free(content);
}

size_t					ft_get_len(t_list *list)
{
	size_t				len;
	t_list				*ptr;

	ptr = list;
	len = 0;
	while (ptr)
	{
		len += ft_strlen((char *)ptr->content) + 1;
		ptr = ptr->next;
	}
	return (len);
}

void					ft_get_str(t_list *list, char **str)
{
	t_list				*ptr;
	int					i;
	int					n;

	*str = ft_strnew(ft_get_len(list));
	ptr = list;
	i = 0;
	while (ptr)
	{
		n = 0;
		while (((char *)ptr->content)[n])
			(*str)[i++] = ((char *)ptr->content)[n++];
		(*str)[i++] = (ptr->next ? '\n' : '\0');
		ptr = ptr->next;
	}
	printf("STR = %s\n", *str);
}

char					*ft_ls(void)
{
	DIR					*dirp;
	struct dirent		*read;
	t_list				*list;
	char				*str;

	list = NULL;
	dirp = opendir(".");
	while ((read = readdir(dirp)))
	{
		ft_listadd_end(&list,
				ft_listnew(read->d_name, ft_strlen(read->d_name)));
	}
	closedir(".");
	ft_get_str(list, &str);
	ft_lstdel(&list, ft_del_elem);
	return (str);
}