/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/11 14:42:37 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

void    ft_redirect(t_redir *redir, char **env, t_env **env_list)
{
	int		fd_file;
	t_exec	*ex;
	int		pid;

	ex = (t_exec *)redir->cmd;
	fd_file = open(redir->file, redir->mode, 0644);
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		dup2(fd_file, redir->fd);
		close(fd_file);
		ft_exec_nofork(ex, env, env_list);
	}
	close(fd_file);
	wait(&g.exit_status);
}