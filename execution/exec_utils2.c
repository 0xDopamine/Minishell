/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:30:04 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/10 17:23:15 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_cmdpath(char *cmd, char **env, char **av)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
	{
		execve(cmd, av, env);
		perror("execv");
		exit(1);
	}
	return (1);
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
			g.exit_status = EXIT_FAILURE;
			return (-1);
		}
		if (pid)
		if (pid)
		if (pid == 0)
		{
			execve(cmd, av, env);
			exit(1);
		}
	}
	else
		return (EXIT_SUCCESS);
	wait(&g.exit_status);
	if (g.exit_status == 127)
	{
		printf("here\n");
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (g.exit_status == 256)
	{
		printf("no here\n");
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}