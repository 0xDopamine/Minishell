/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:29:25 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/06 15:45:51 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	export_checkpathname(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97
				&& str[i] <= 122) && str[i] != '_')
		{
			ft_putstr_fd("export: '", str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

static	int	export_ifexists(char *name, char *path, t_env **env)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = *env;
	while (lst)
	{
		if (!ft_strncmp(name, lst->name, ft_strlen(name)))
		{
			if (lst->path == NULL && path[0] == 0)
				return (1);
			if (path[0] == 0)
				return (1);
			free(lst->path);
			lst->path = ft_strdup(path);
			free(name);
			free(path);
			return (1);
		}
		i++;
		lst = lst->next;
	}
	return (0);
}

static	int	export_checkav(char *str, char **ptr, int n)
{
	int	i;

	i = 0;
	if (n == NAME)
		return (export_checkname(str));
	else
	{
		if (str[0] == 0)
		{
			ptr[1] = NULL;
			return (1);
		}
		return (export_checkpath(str));
	}
	return (1);
}

int	ft_export(t_env **env, t_exec *line)
{
	char	**str;
	int		i;

	str = NULL;
	i = 0;
	if (!line->argv[1])
		return (ft_env(*env, 'e'));
	str = ft_split_namecont(line->argv[1]);
	if (!str || !str[0])
		return (1);
	if (export_ifexists(str[0], str[1], env))
	{
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	if (export_checkav(str[0], str, NAME) && export_checkav(str[1], str, PATH))
		ft_lstadd_back(env, ft_lstnew(str[1], str[0]));
	g.exit_status = EXIT_SUCCESS;
	return (1);
}
