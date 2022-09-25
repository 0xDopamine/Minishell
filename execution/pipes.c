/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:32:15 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// static	void	access_loop(char *cmd)
// {
// 	char	*join;
// 	char	**path;
// 	int		i;

// 	i = 0;
// 	path = ft_find_path();
// 	while (path[i])
// 	{
// 		join = ft_strjoin(path[i], cmd);
// 		if (access(join, X_OK) == 0)
// 		{
// 			ft_free_doubleptr(path);
// 			g_var.exit_status = EXIT_SUCCESS;
// 			return ;
// 		}
// 		free(join);
// 		i++;
// 	}
// 	ft_free_doubleptr(path);
// 	g_var.exit_status = EXIT_NOTFOUND;
// }

// void	pipes_access(t_exec *line)
// {
// 	char	*cmd;
// 	char	*tmp;

// 	if (!line->argv[0])
// 		return ;
// 	cmd = ft_strdup(line->argv[0]);
// 	if (exec_checkcmd(cmd))
// 	{
// 		free(cmd);
// 		g_var.exit_status = EXIT_SUCCESS;
// 		return ;
// 	}
// 	tmp = ft_strjoin("/", cmd);
// 	access_loop(cmd);
// 	free (cmd);
// 	free (tmp);
// }

void	ft_pipes(t_pipe *pipes, t_env **env_list, int *in)
{
	int	fds[2];

	pipe(fds);
	ft_start_pipe(pipes->left, in, fds, env_list);
	close(fds[1]);
	ft_start_pipe(pipes->right, &fds[0], (int[2]){0, 1}, env_list);
	close(fds[0]);
}

