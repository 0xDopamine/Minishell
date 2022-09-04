/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/04 17:33:04 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_redirect(t_redir *redir, char **env, t_env **env_list)
{
	int		fd_file;
	t_exec	*ex;
	t_redir	*redir2;
	t_cmd	*cmd;
	int		pid;

	redir2 = (t_redir *)redir->left;
	cmd = (t_cmd *)redir->left;
	ex = (t_exec *)redir->right;
	ft_heredoc(env_list);
	fd_file = open(redir->file, redir->mode, 0644);
	if (fd_file < 0)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
		return ;
	}
	if (cmd->type == REDIR && redir2->fd == redir->fd)
	{
		ft_redirect((t_redir *)redir->left, env, env_list);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		dup2(fd_file, redir->fd);
		// if (redir->)
		ft_exec_nofork(ex, env, env_list);
		ft_putstr_fd(ex->argv[0], ": command not found\n", STDERR_FILENO);
		close(fd_file);
		exit(EXIT_FAILURE);
	}
	close(fd_file);
	wait(&g.exit_status);
	if (g.exit_status == 256)
		g.exit_status = EXIT_NOTFOUND;
	else
		g.exit_status = EXIT_SUCCESS;
}
