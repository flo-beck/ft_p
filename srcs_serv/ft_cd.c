/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 15:56:00 by fbeck             #+#    #+#             */
/*   Updated: 2014/05/18 22:04:15 by fbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ftp.h"

static int				ft_check_depth(t_e *e, char *path)
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
	ft_free_split(&split);
	return (depth);
}

static void				ft_goto_root(t_e *e)
{
	int					res;
	char				*tmp;

	res = chdir(e->serv_root);
	if (res == 0)
	{
		tmp = e->curr_pwd;
		e->curr_pwd = ft_strdup("/");
		e->depth = 0;
		free(tmp);
	}
	else
		ft_error("[ERROR: Failed to change to root			]");
}

static void				ft_update_pwd(t_e *e)
{
	char				*new_pwd;
	char				*tmp;
	int					i;

	tmp = e->curr_pwd;
	new_pwd = getcwd(NULL, MAXPATHLEN);
	i = ft_strlen(e->serv_root);
	e->curr_pwd = (new_pwd[i] == '\0' ?
			ft_strdup("/") : ft_strdup(&new_pwd[i]));
	free(new_pwd);
	free(tmp);
}

static char				*ft_move_dir(t_e *e, char *path, int depth)
{
	int					res;

	res = chdir(path);
	if (res == 0)
	{
		ft_update_pwd(e);
		e->depth = depth;
		return (ft_strdup("SUCCESS: changed directory "));
	}
	else
		return (ft_strjoin("Error: Could not change directory to ", path));
}

char					*ft_cd(t_e *e, char *buf)
{
	char				*path;
	int					i;
	char				*msg;
	int					depth;

	i = 3;
	while (buf[i] != '\0' && ft_isblank(buf[i]))
		i++;
	path = &buf[i];
	depth = ft_check_depth(e, path);
	if (depth >= 0)
	{
		msg = ft_move_dir(e, path, depth);
	}
	else
	{
		ft_putendl("[ERROR: Server cant go that far		]");
		ft_goto_root(e);
		msg = ft_strdup("SUCCESS: changed directory ");
	}
	return (msg);
}
