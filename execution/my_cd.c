/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:13:11 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	cd_norme(void)
{
	perror("cd");
	g_var.exit_status = EXIT_FAILURE;
	return (0);
}

static	int	cd_update_pwd(t_env **env_list)
{
	t_env	*env;
	char	*pwd;

	env = *env_list;
	pwd = getcwd(NULL, 0);
	if (!getcwd(pwd, PATH_MAX))
	{
		free(pwd);
		perror("cd");
		g_var.exit_status = EXIT_FAILURE;
		return (1);
	}
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 3))
		{
			if (env->path)
				free(env->path);
			env->path = ft_strdup(pwd);
			break ;
		}
		env = env->next;
	}
	free(pwd);
	return (0);
}

int	cd_oldpwd(t_env **env_list)
{
	char	*pwd;
	t_env	*env;

	pwd = getcwd(NULL, 0);
	env = *env_list;
	while (env)
	{
		if (!ft_strncmp(env->name, "OLDPWD", 6))
		{
			getcwd(pwd, PATH_MAX);
			if (chdir(env->path) < 0)
				return (cd_norme());
			g_var.exit_status = EXIT_SUCCESS;
			if (env->path)
				free(env->path);
			env->path = ft_strdup(pwd);
			free(pwd);
			cd_update_pwd(env_list);
			return (1);
		}
		env = env->next;
	}
	free(pwd);
	return (1);
}

static	int	cd_update_oldpwd(t_env **env_list)
{
	t_env	*env;
	char	*pwd;

	env = *env_list;
	pwd = getcwd(NULL, 0);
	if (!getcwd(pwd, PATH_MAX))
	{
		free(pwd);
		g_var.exit_status = EXIT_FAILURE;
		return (0);
	}
	while (env)
	{
		if (!ft_strncmp(env->name, "OLDPWD", 6))
		{
			if (env->path)
				free(env->path);
			env->path = ft_strdup(pwd);
			break ;
		}
		env = env->next;
	}
	free(pwd);
	return (0);
}

int	ft_cd(t_exec *line, t_env **env_list)
{
	if (cd_ifoldpwd(line->argv[1], env_list))
		return (1);
	if (cd_update_oldpwd(env_list))
		return (cd_errors());
	if (!line->argv[1])
	{
		if (!cd_home())
			return (1);
	}
	if (chdir(line->argv[1]) < 0 && line->argv[1])
	{
		printf("hahowa line %s\n", line->argv[1]);
		perror("cd");
		return (cd_errors());
	}
	if (cd_update_pwd(env_list))
		return (cd_errors());
	g_var.exit_status = EXIT_SUCCESS;
	return (1);
}
