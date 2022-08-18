/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:47:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/18 15:37:22 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_check_cmd(t_cmd *cmd, char **env, t_env **env_list)
{
	if (cmd->type == EXEC)
		ft_exec((t_exec *)cmd, env, env_list);
	if (cmd->type == REDIR)
		ft_redirect((t_redir *)cmd, env, env_list);
	if (cmd->type == PIPE)
		ft_pipes((t_pipe *)cmd, env, env_list);
}

static	int	exec_checkcmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

static	void	exec_loop(char *cmd, char **av, char **env)
{
	int		i;
	char	*join;
	char	**path;

	i = 0;
	path = ft_find_path();
	while (path[i])
	{
		if (!exec_checkcmd(cmd))
			join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			ft_free_doubleptr(path);
			if (execve(join, av, env) < 0)
				perror("execve");
			break ;
		}
		free(join);
		i++;
	}
}

void	ft_exec(t_exec *line, char **env, t_env **env_list)
{
	char	*cmd;
	int		pid;

	if (!line->argv[0])
		return ;
	cmd = ft_strdup(line->argv[0]);
	if (ft_builtins(cmd, line, env_list))
		return ;
	if (!exec_checkcmd(cmd))
		cmd = ft_strjoin("/", cmd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		exec_loop(cmd, line->argv, env);
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		exit(1);
	}
	free(cmd);
	wait(&g.exit_status);
	return ;
}
