/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:13:11 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/16 17:49:40 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	cd_update_pwd(t_env **env_list)
{
	t_env	*env;
	char	*pwd;

	env = *env_list;
	pwd = getcwd(NULL, 0);
	if (!getcwd(pwd, PATH_MAX))
	{
		perror("cd");
		return (1);
	}
	while (env)
	{
		if (!ft_strncmp(env->type, "PWD", 3))
		{
			if (env->content)
				free(env->content);
			env->content = pwd;
			break ;
		}
		env = env->next;
	}
	return (0);
}

static	int	cd_update_oldpwd(t_env **env_list)
{
	t_env	*env;
	char	*pwd;

	env = *env_list;
	pwd = getcwd(NULL, 0);
	if (!getcwd(pwd, PATH_MAX))
	{
		perror("cd");
		return (1);
	}
	while (env)
	{
		if (!ft_strncmp(env->type, "OLDPWD", 6))
		{
			if (env->content)
				free(env->content);
			env->content = pwd;
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	ft_cd(t_exec *line, t_env **env_list)
{
	t_env	*env;

	env = *env_list;
	if (cd_update_oldpwd(env_list))
	{
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	if (!line->argv[1])
	{
		if (chdir(getenv("HOME")) < 0)
		{
			perror("cd");
			g.exit_status = 2;
			return (1);
		}
	}
	if (chdir(line->argv[1]) < 0 && line->argv[1])
	{
		perror("cd");
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	if (cd_update_pwd(env_list))
	{
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	g.exit_status = EXIT_SUCCESS;
	return (1);
}
