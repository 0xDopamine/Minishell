/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_specialcase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:01:32 by abaioumy         #+#    #+#              */
/*   Updated: 2022/09/25 19:07:47 by abaioumy        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_isdir(char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

static int	ft_check_if_dir(char *cmd)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = getcwd(s, PATH_MAX);
	if (exec_isdir(cmd) || ft_strcmp(cmd, tmp) == 0)
	{
		free(s);
		free(tmp);
		ft_putstr_fd(cmd, ": is a directory\n", STDERR_FILENO);
		exit(126);
		return (EXIT_FAILURE);
	}
	free(s);
	free(tmp);
	return (EXIT_SUCCESS);
}

int	exec_specialcases(char *cmd, t_exec *line, char **my_env, t_env **env_list)
{
	if (ft_check_if_dir(cmd))
	{
		freethis(my_env);
		free(cmd);
		return (1);
	}
	if (exec_checkcmd_fork(cmd, line->argv, my_env) == -1)
	{
		freethis(my_env);
		free(cmd);
		freethis(line->argv);
		return (1);
	}
	if (ft_ifmybuiltin(cmd, line, env_list)
		|| ft_ifmybuiltin_up(cmd, line, env_list))
	{
		free(cmd);
		freethis(my_env);
		exit(EXIT_SUCCESS);
		return (1);
	}
	return (0);
}
