/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:12:41 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/13 16:19:38 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_get_env(char **env, t_env **env_list)
{
	int i;
	char	**str;

	i = 0;
	while (env[i])
	{
		str = ft_split_typecont(env[i]);
		ft_lstadd_back(env_list, ft_lstnew(str[1], str[0]));
		i++;
	}
	return ;
}

static	char	*env_findenv(char *env, t_env *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if (!ft_strncmp(env, env_list->type, ft_strlen(env_list->type)))
			return (env_list->content);
		env_list = env_list->next;
	}
	return (0);
}

static	void	env_printenv(t_env *env_list)
{
	while (env_list)
	{
		printf("%s", env_list->type);
		printf("=");
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
	g.exit_status = EXIT_SUCCESS;
}
int	ft_env(t_env *env_list, char **av)
{
	if (av[1])
	{
		g.exit_status = 127;
		if (av[1][0] == '$')
		{
			if (!getenv(&av[1][1]) && !env_findenv(&av[1][1], env_list))
			{
				env_printenv(env_list);
				g.exit_status = EXIT_SUCCESS;
				return (1);
			}
			ft_putstr_fd("env: ", STDERR_FILENO);
			if (env_findenv(&av[1][1], env_list))
				ft_putstr_fd(env_findenv(&av[1][1], env_list), STDERR_FILENO);
			else
				ft_putstr_fd(getenv(&av[1][1]), STDERR_FILENO);
			ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
			return (1);
		}
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(&av[1][1], STDERR_FILENO);
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
		return (1);
	}
	env_printenv(env_list);
	return (1);
}
