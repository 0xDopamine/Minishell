/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:12:41 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/17 18:40:53 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_get_env(char **env, t_env **env_list)
{
	int		i;
	char	**str;

	i = 0;
	while (env[i])
	{
		str = ft_split_namecont(env[i]);
		ft_lstadd_back(env_list, ft_lstnew(str[1], str[0]));
		if (str[0])
			free(str[0]);
		if (str[1])
			free(str[1]);
		free(str);
		i++;
	}
	return ;
}

static	void	export_printenv(t_env *env_list)
{
	char	**names;
	t_env	*list;
	int		i;

	i = 0;
	list = env_list;
	names = export_sortnames(env_list);
	while (i < ft_lstsize(env_list))
	{
		printf("declare -x ");
		printf("%s", names[i]);
		list = env_list;
		env_printloop(list, names, i);
		i++;
	}
	g.exit_status = EXIT_SUCCESS;
}

static	void	env_printenv(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->path != NULL && env_list->ifnull != 1)
		{
			printf("%s", env_list->name);
			printf("=");
			printf("%s\n", env_list->path);
		}
		env_list = env_list->next;
	}
	g.exit_status = EXIT_SUCCESS;
}

int	ft_env(t_env *env_list, char c)
{
	if (c == EXP)
	{
		export_printenv(env_list);
		return (1);
	}
	env_printenv(env_list);
	return (1);
}
