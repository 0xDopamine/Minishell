/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:32:15 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/22 12:28:40 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

static	void	pipes_access(t_exec *line)
{
	char	**path;
	int		i;
	char	*cmd;
	char	*join;

	i = 0;
	cmd = ft_strdup(line->argv[0]);
	if (exec_checkcmd(cmd))
	{
		g.exit_status = EXIT_SUCCESS;
		return ;
	}
	cmd = ft_strjoin("/", cmd);
	path = ft_find_path();
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			ft_free_doubleptr(path);
			g.exit_status = EXIT_SUCCESS;
			return ;
		}
		free(join);
		i++;
	}
	g.exit_status = EXIT_NOTFOUND;
}

static	int	ft_check_type(t_cmd *cmd, char **env, t_env **env_list, int n)
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
	if (ft_check_type((t_cmd *)pipes->left, env, env_list, 0))
		pipes_access((t_exec *)pipes->left);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		if (ft_check_type((t_cmd *)pipes->left, env, env_list, 0))
			ft_exec_nofork((t_exec *)pipes->left, env, env_list);
		exit(EXIT_FAILURE);
	}
	if (ft_check_type((t_cmd *)pipes->right, env, env_list, 1))
		pipes_access((t_exec *)pipes->right);
	pid = fork();
	if (pid == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
		if (ft_check_type((t_cmd *)pipes->right, env, env_list, 1))
			ft_exec_nofork((t_exec *)pipes->right, env, env_list);
		exit(EXIT_FAILURE);
	}
	close(fds[0]);
	close(fds[1]);
	wait(NULL);
	wait(NULL);
}
