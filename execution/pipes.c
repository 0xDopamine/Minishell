/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:32:15 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/12 14:34:04 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

static int	ft_check_type(t_cmd *cmd, char **env, t_env **env_list, int n)
{
	if (cmd->type == EXEC)
		return (1);
	if (cmd->type == REDIR)
	{
		ft_redirect((t_redir *)cmd, env, env_list);
		return (0);
	}
	if (cmd->type == PIPE && n == 1)
	{
		write(2, "ps\n", 3);
		ft_pipes((t_pipe *)cmd, env, env_list);
		return (0);
	}
	return (0);
}

void	ft_pipes(t_pipe *pipes, char **env, t_env **env_list)
{
	int	fds[2];
	int	pid;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		if (ft_check_type((t_cmd *)pipes->left, env, env_list, 0))
			ft_exec_nofork((t_exec *)pipes->left, env, env_list);
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
		if (ft_check_type((t_cmd *)pipes->right, env, env_list, 1))
			ft_exec_nofork((t_exec *)pipes->right, env, env_list);
		exit(1);
	}
	close(fds[0]);
	close(fds[1]);
	wait(&g.exit_status);
	wait(&g.exit_status);
}
