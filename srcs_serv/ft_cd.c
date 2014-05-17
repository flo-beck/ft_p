/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 15:56:00 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/17 14:11:40 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ftp.h"


/*     int chdir(const char *path);*/
 #include <unistd.h>

     /*char *
	      getcwd(char *buf, size_t size);*/

/* " cd ../../../.."*/

int						ft_check_depth(t_e *e, char *path)
{
	int					depth;
	char				**split;
	int					i;

	split = ft_strsplit(path, '/');
	i = 0;
	depth = e->depth;
	while (split[i])
	{
		if (!ft_strcmp(split[i], ".."))
			depth--;
		else if (ft_strcmp(split[i], "."))
			depth++;
		i++;
	}
	return (depth);
}

static void				ft_goto_root(t_e *e)
{
	int					res;

	res = chdir(e->serv_root);
	if (res == 0)
	{
		e->curr_pwd = ft_strdup("/");
		e->depth = 0;
	}
	else
		ft_error("Failed to change to root");
}

void					ft_update_pwd(t_e *e)
{
	char				*new_pwd;
	int					i;

	new_pwd = getcwd(NULL, MAXPATHLEN);
	printf("serv_root [%s]\ncurr_pwd  [%s]\n new pwd [%s]\n", e->serv_root, e->curr_pwd, new_pwd );
	i = ft_strlen(e->serv_root);
	e->curr_pwd = (new_pwd[i] == '\0' ? ft_strdup("/") : ft_strdup(&new_pwd[i]));
	printf("NEW PWD = %s\n", e->curr_pwd );
}

char					*ft_cd(t_e *e, char *buf)
{
	char				*path;
	int					i;
	int					res;
	char				*msg;
	int					depth;

	i = 3;
	printf("buf [%s] buf[i] [%s]\n",buf, &buf[i] );
	while (buf[i] != '\0' && ft_isblank(buf[i]))
		i++;
	path = &buf[i];
	depth = ft_check_depth(e, path);
	if (depth >= 0)
	{
		res = chdir(path);
		if (res == 0)
		{
			ft_update_pwd(e);
			e->depth = depth;
			msg = ft_strjoin("SUCCESS - changed dir to ", e->curr_pwd);
		}
		else
			msg = ft_strjoin("FAILED to change dir to ", path);
	}
	else
	{
		printf("cant go that far!!!\n");
		ft_goto_root(e);
		msg = ft_strjoin("SUCCESS - changed dir to ", e->curr_pwd);
	}
	return (msg);
}
