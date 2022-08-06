/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:32:15 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/06 14:48:41 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

void    ft_pipes(t_pipe *pipes, char **env, t_env **env_list)
{
	int fds[2];
	int	pid;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[1], 1);
		// close(fds[0]);
		printf("%d\n", close(fds[0]));
		ft_exec((t_exec *)pipes->left, env, env_list);
	}
	close(fds[1]);
	// close(fds[0]);
	if (!pipes->right)
	{
		close(fds[0]);
		close(fds[1]);
		wait(NULL);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		// close(fds[1]);
		ft_exec((t_exec *)pipes->right, env, env_list);
	}
	close(fds[0]);
	wait(NULL);
	wait(NULL);
	// ft_pipes(pipes->,)
}