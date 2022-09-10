/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:32:15 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/10 17:59:46 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	pipes_access(t_exec *line)
{
	char	**path;
	int		i;
	char	*cmd;
	char	*join;

	i = 0;
	if (!line->argv[0])
		return ;
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

void	ft_pipes(t_pipe *pipes, char **env, t_env **env_list)
{
	int	fds[2];

	pipe(fds);
	if (pipes_fork_left(pipes, fds, env, env_list) == -1)
		return ;
	if (pipes_fork_right(pipes, fds, env, env_list) == -1)
		return ;
	close(fds[0]);
	close(fds[1]);
	wait(NULL);
	wait(NULL);
}
