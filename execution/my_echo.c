/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:01:03 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/16 17:49:55 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	echo_check_nl(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n' && str[2] != 'n' && str[2] != '\0')
		return (0);
	if (str[0] == '-' && str[1] == 'n')
		return (1);
	return (0);
}

static void	echo_ifnewline(t_exec *line, int i, int ifnl)
{
	if (ifnl)
	{
		printf("%s", line->argv[i++]);
		while (line->argv[i])
			printf(" %s", line->argv[i++]);
	}
	else
	{
		i = 1;
		printf("%s", line->argv[i++]);
		if (!line->argv[i])
			printf("\n");
		while (line->argv[i])
			printf(" %s\n", line->argv[i++]);
	}
}

static	void	echo_find_env(char *env, t_env *env_list, int ifnl)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if (!ft_strncmp(&env[1], env_list->type, ft_strlen(env_list->type)))
			printf("%s", env_list->content);
		env_list = env_list->next;
	}
	if (!ifnl)
		printf("\n");
}

int	ft_echo(t_exec *line, t_env *env_list)
{
	int	i;
	int	ifnl;

	i = 1;
	ifnl = 0;
	if (!line->argv[1])
	{
		g.exit_status = EXIT_SUCCESS;
		printf("\n");
		return (1);
	}
	if (!ft_strncmp(line->argv[1], "$?", 2))
	{
		printf("%d\n", g.exit_status);
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	while (echo_check_nl(line->argv[i]))
	{
		ifnl = 1;
		i++;
	}
	printf("%d\n", i);
	if (!line->argv[i])
	{
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	if (!ft_strncmp(line->argv[1], "$", 1)
		|| !ft_strncmp(line->argv[i], "$", 1))
	{
		if (ifnl)
			echo_find_env(line->argv[i], env_list, ifnl);
		else
			echo_find_env(line->argv[1], env_list, ifnl);
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	if (ifnl)
		echo_ifnewline(line, i, ifnl);
	else
		echo_ifnewline(line, i, ifnl);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}