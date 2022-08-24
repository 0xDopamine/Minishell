/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:47:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/24 19:40:31 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_checkcmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

static	void	exec_loop(char *cmd, char **av, char **env)
{
	char	*join;
	int		pid;

	if (exec_checkcmd(cmd))
	{
		if (execve(cmd, av, env) < 0)
			perror("execve");
	}
	join = exec_ifaccess(cmd);
	if (join != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(join, av, env);
			perror("execve");
			exit(1);
		}
		free(join);
	}
	if (wait(NULL) < 0)
	{
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
	}
}

void	ft_exec(t_exec *line, char **env, t_env **env_list)
{
	char	*cmd;

	// printf("%s\n", line->argv[0]);
	if (!line->argv[0])
		return ;
	cmd = ft_strdup(line->argv[0]);
	if (ft_builtins(cmd, line, env_list))
		return ;
	if (!exec_checkcmd(cmd))
		cmd = ft_strjoin("/", cmd);
	exec_loop(cmd, line->argv, env);
	free(cmd);
	return ;
}
