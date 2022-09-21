/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:30:04 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle(int sig)
{
	sig = 1;
	ft_exit(NULL);
}

static	int	exec_check_exitcode(char *cmd)
{
	if (g_var.exit_status == 127)
	{
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (g_var.exit_status == 256)
	{
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		g_var.exit_status = EXIT_NOTFOUND;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exec_cmdpath(char *cmd, char **env, char **av)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_var.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, handle);
		execve(cmd, av, env);
		perror("execve");
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
		return (EXIT_SUCCESS);
	wait(&g_var.exit_status);
	if (exec_check_exitcode(cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
