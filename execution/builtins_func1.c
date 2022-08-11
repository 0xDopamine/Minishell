/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:16:58 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/11 17:51:13 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_exit(void)
{
	g.ifexit = 0;
	return (1);
}

static int	ft_check_nl(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n')
		return (1);
	return (0);
}

static void ft_find_env(char *env, t_env *env_list, int ifnl)
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
	int i;
	int	ifnl;

	i = 1;
	ifnl = 0;
	if (!line->argv[1])
	{
		printf("\n");
		return (1);
	}
	if (!ft_strncmp(line->argv[1], "$?", 2))
	{
		printf("%d\n", g.exit_status);
		return (1);
	}
	while (ft_check_nl(line->argv[i]))
	{
		ifnl = 1; 
		i++;
	}
	if (!ft_strncmp(line->argv[1], "$", 1) || !ft_strncmp(line->argv[2], "$", 1))
	{
		if (ifnl)
			ft_find_env(line->argv[2], env_list, ifnl);
		else
			ft_find_env(line->argv[1], env_list, ifnl);
		return (1);
	}
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
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

int	ft_unset(t_env **env, t_exec *line)
{
	t_env	*env2;
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	env2 = *env;
	prev = env2;
	while (env2)
	{
		if (ft_envcmp(env2->type, line->argv[1]))
		{
			temp = env2;
			prev->next = temp->next;
			ft_lstdelone(env2, del);
			break ;
		}
		prev = env2;
		env2 = env2->next;
	}
	g.exit_status = EXIT_SUCCESS;
	return (1);
}