/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:30:04 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/09 15:10:06 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_checkcmd_fork(char *cmd, char **av, char **env)
{
	int	pid;

	if (exec_checkcmd(cmd))
	{
		pid = fork();
		if (pid == 0)
		{
			execve(cmd, av, env);
			exit(1);
		}
	}
	else
		return ;
	wait(&g.exit_status);
	if (g.exit_status == 127)
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
	if (g.exit_status == 256)
	{
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
	}
}