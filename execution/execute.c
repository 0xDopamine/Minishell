/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:27:29 by codespace         #+#    #+#             */
/*   Updated: 2022/09/25 15:46:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_checkcmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

int	exec_checkcmd_fork(char *cmd, char **av, char **env)
{
	int	pid;

	if (exec_checkcmd(cmd))
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			g_var.exit_status = EXIT_FAILURE;
			return (-1);
		}
		if (pid == 0)
		{
			execve(cmd, av, env);
			exit(1);
		}
	}
	else
		return (EXIT_FAILURE);
	g_var.exit_status = EXIT_SUCCESS;
	return (-1);
}

static	int	ft_check_if_dir(char *cmd)
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
		return (EXIT_FAILURE);
	}
	free(s);
	free(tmp);
	return (EXIT_SUCCESS);
}

void	execnofork_loop(char *cmd, char **av, char **env)
{
	char	**path;
	char	*join;
	int		i;

	i = 0;
	path = ft_find_path();
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			ft_free_doubleptr(path);
			execve(join, av, env);
			perror("execve");
			free (join);
			return ;
		}
		free(join);
		i++;
	}
	g_var.exit_status = EXIT_NOTFOUND;
	ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
	ft_free_doubleptr(path);
	exit(EXIT_NOTFOUND);
}

void	ft_exec_nofork(t_exec *line, t_env **env_list)
{
	char	*cmd;
	char	*tmp;
	char	**my_env;

	if (!line->argv[0])
	{
		g_var.exit_status = EXIT_FAILURE;
		return ;
	}
	cmd = ft_strdup(line->argv[0]);
	if (ft_check_if_dir(cmd))
	{
		free(cmd);
		return ;
	}
	my_env = ft_myenv(*env_list);
	if (exec_checkcmd_fork(cmd, line->argv, my_env) == -1)
	{
		freethis(my_env);
		free(cmd);
		freethis(line->argv);
		return ;
	}
	if (ft_ifmybuiltin(cmd, line, env_list)
		|| ft_ifmybuiltin_up(cmd, line, env_list))
	{
		free(cmd);
		freethis(my_env);
		exit(EXIT_SUCCESS);
		return ;
	}
	tmp = ft_strjoin("/", cmd);
	execnofork_loop(tmp, line->argv, my_env);
	freethis(line->argv);
	free(cmd);
	free(tmp);
	freethis(my_env);
}
