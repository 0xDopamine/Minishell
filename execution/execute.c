/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:27:29 by abaioumy         #+#    #+#              */
/*   Updated: 2022/09/25 19:06:17 by abaioumy        ###   ########.fr        */
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
			exit(EXIT_FAILURE);
		}
	}
	else
		return (EXIT_FAILURE);
	return (-1);
}

void	execnofork_loop(char *cmd, char **av, char **env)
{
	char	**path;
	char	*join;
	int		i;

	i = 0;
	path = ft_find_path();
	while (path && path[i])
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
	my_env = ft_myenv(*env_list);
	if (exec_specialcases(cmd, line, my_env, env_list))
		return ;
	tmp = ft_strjoin("/", cmd);
	execnofork_loop(tmp, line->argv, my_env);
	// freethis(line->argv);
	// free(cmd);
	free(tmp);
	freethis(my_env);
}
