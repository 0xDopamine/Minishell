/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:29:25 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/13 13:20:36 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int export_checktype(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122) && str[i] != '_')
		{
			ft_putstr_fd("export: '", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

static	int	ft_ifexists_export(char *type, char *content, t_env **env)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = *env;
	while (lst)
	{
		if (!ft_strncmp(type, lst->type, ft_strlen(lst->type)))
		{
			free(lst->content);
			lst->content = content;
			return (1);
		}
		i++;
		lst = lst->next;
	}
	return (0);
}

static int ft_check_export(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122) && str[i] != '=' && str[i] != '+' && str[i] != '-' && str[i] != '_')
			return (0);
		if ((str[i] == '+' || str[i] == '-') && str[i+1] == '=')
		{
			ft_putstr_fd("export: not valid in this context\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_env **env, t_exec *line)
{
	char	**str;

	str = NULL;
	if (!line->argv[1])
		return (ft_env(*env));
	str = ft_split_typecont(line->argv[1]);
	if (!str || !str[0])
		return (1);
	if (ft_ifexists_export(str[0], str[1], env))
		return (1);
	if (ft_check_export(line->argv[1]))
	{
		ft_lstadd_back(env, ft_lstnew(str[1], str[0]));
	}
	else
		printf("error\n");
	return (1);
}
