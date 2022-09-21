/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:47:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:14:44 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_checkcmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

static	void	exec_loop2(char *cmd, char **av, char **env)
{
	char	*join;

	join = NULL;
	if (exec_checkcmd_fork(cmd, av, env) == -1)
		return ;
	join = exec_ifaccess(cmd);
	if (join != NULL)
	{
		if (exec_cmdpath(join, env, av) == -1)
			return ;
		free(join);
	}
	g_var.exit_status = EXIT_SUCCESS;
	if (wait(&g_var.exit_status) < 0)
	{
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		g_var.exit_status = EXIT_NOTFOUND;
	}
}

static	void	exec_loop(char *cmd, char **av, char **env)
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
		g_var.exit_status = 126;
		return ;
	}
	free(s);
	free(tmp);
	exec_loop2(cmd, av, env);
}

void	ft_exec(t_exec *line, t_env **env_list)
{
	char	*cmd;
	char	*tmp;
	char	**my_env;

	if (!line->argv[0])
		return ;
	cmd = ft_strdup(line->argv[0]);
	my_env = ft_myenv(*env_list);
	if (ft_ifmybuiltin(cmd, line, env_list)
		|| ft_ifmybuiltin_up(cmd, line, env_list))
	{
		freethis(my_env);
		free(cmd);
		return ;
	}
	if (!exec_checkcmd(cmd))
	{
		tmp = cmd;
		cmd = ft_strjoin("/", cmd);
		free(tmp);
	}
	exec_loop(cmd, line->argv, my_env);
	freethis(my_env);
	free(cmd);
	return ;
}
