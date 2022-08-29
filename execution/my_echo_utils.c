/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:30:38 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/29 02:18:49 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	void	echo_find_env(char *env, t_env *env_list, int ifnl)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if (!ft_strncmp(&env[1], env_list->name, ft_strlen(env_list->name)))
			printf("%s", env_list->path);
		env_list = env_list->next;
	}
	if (!ifnl)
		printf("\n");
}

int	echo_case1(char *str)
{
	if (!str)
	{
		g.exit_status = EXIT_SUCCESS;
		printf("\n");
		return (1);
	}
	if (!ft_strncmp(str, "$?", 2))
	{
		printf("%d\n", g.exit_status);
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	return (0);
}

int	echo_path(char **av, int i, t_env *env_list, int ifnl)
{
	if (!ft_strncmp(av[1], "$", 1)
		|| !ft_strncmp(av[i], "$", 1))
	{
		if (ifnl)
			echo_find_env(av[i], env_list, ifnl);
		else
			echo_find_env(av[1], env_list, ifnl);
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	else
		return (0);
}
