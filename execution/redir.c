/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/05 15:58:22 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_redirect(t_redir *redir, char **env, t_env **env_list)
{
	int	fd_file;
	t_exec	*ex;
	t_red	red;
	int		pid;

	red.in_fd = -1024;
	red.out_fd = -1024;
	fd_file = 0;
	ex = (t_exec *)redir->right;
	while (redir && redir->fd == STDIN_FILENO)
	{
		fd_file = open(redir->file, redir->mode, 0644);
		red.in_fd = fd_file;
		if (red.in_fd == -1)
		{
			ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			g.exit_status = EXIT_NOTFOUND;
			return ;
		}
		redir = (t_redir *)redir->left;
	}
		// int i = 0;
	while (redir && redir->fd == STDOUT_FILENO)
	{
		fd_file = open(redir->file, redir->mode, 0644);
		red.out_fd = fd_file;
		if (red.out_fd == -1)
		{
			ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			g.exit_status = EXIT_NOTFOUND;
			return ;
		}
		redir = (t_redir *)redir->left;
	}
	pid = fork();
	if (pid == 0)
	{
		if (red.in_fd != -1024 && red.in_fd != -1)
			dup2(red.in_fd, STDIN_FILENO);
		if (red.out_fd != -1024 && red.out_fd != -1)
			dup2(red.out_fd, STDOUT_FILENO);
		ft_exec_nofork(ex, env, env_list);
	}
	wait(&g.exit_status);
	if (g.exit_status == 256)
		g.exit_status = EXIT_NOTFOUND;
	else
		g.exit_status = EXIT_SUCCESS;
}

// void	ft_redirect(t_redir *redir, char **env, t_env **env_list)
// {
// 	int		fd_file;
// 	t_exec	*ex;
// 	t_redir	*redir2;
// 	t_cmd	*cmd;
// 	int		pid;

// 	redir2 = (t_redir *)redir->left;
// 	cmd = (t_cmd *)redir->left;
// 	ex = (t_exec *)redir->right;
// 	// printf("%s\n%s\n", ex->argv[0], ex->argv[1]);
// 	fd_file = open(redir->file, redir->mode, 0644);
// 	if (fd_file < 0)
// 	{
// 		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
// 		ft_putchar_fd('\n', STDERR_FILENO);
// 		g.exit_status = EXIT_NOTFOUND;
// 		return ;
// 	}
// 	if (cmd->type == REDIR && redir2->fd == redir->fd)
// 	{
// 		ft_redirect((t_redir *)redir->left, env, env_list);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		dup2(fd_file, redir->fd);
// 		ft_exec_nofork(ex, env, env_list);
// 		ft_putstr_fd(ex->argv[0], ": command not found\n", STDERR_FILENO);
// 		close(fd_file);
// 		exit(EXIT_FAILURE);
// 	}
// 	close(fd_file);
// 	wait(&g.exit_status);
// 	if (g.exit_status == 256)
// 		g.exit_status = EXIT_NOTFOUND;
// 	else
// 		g.exit_status = EXIT_SUCCESS;
// }
