/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:21:56 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	redir_exit_status(void)
{
	if (g_var.exit_status == 256)
		g_var.exit_status = EXIT_NOTFOUND;
	else
		g_var.exit_status = EXIT_SUCCESS;
}

static	void	redirect_exec(t_red *red, t_here *here
	, t_exec *ex, t_env **env_list)
{
	if (here->fd_creat != -2 && here->fd_creat != -1)
	{
		dup2(here->fd_read, STDIN_FILENO);
		if (red->out_fd != -2 && red->out_fd != -1)
			dup2(red->out_fd, STDOUT_FILENO);
		ft_exec_nofork(ex, env_list);
		close(here->fd_creat);
		close(here->fd_read);
	}
	if (red->in_fd != -2 || red->out_fd != -2)
	{
		if (red->in_fd != -2 && red->in_fd != -1)
			dup2(red->in_fd, STDIN_FILENO);
		if (red->out_fd != -2 && red->out_fd != -1)
			dup2(red->out_fd, STDOUT_FILENO);
		ft_exec_nofork(ex, env_list);
	}
	exit(1);
}

static	int	redirect_loop(t_redir *redir, t_red *red
	, t_here *here, t_env **env_list)
{
	int	infd_dup;

	here->file_path = NULL;
	here->fd_creat = -2;
	red->in_fd = -2;
	red->out_fd = -2;
	infd_dup = dup(0);
	signal(SIGINT, ft_sig_here);
	while (redir)
	{
		if (redir->mode == HEREDOC && !g_var.here_sig)
		{
			if (start_heredoc(here, redir, infd_dup, env_list) == -1)
				return (1);
			close(infd_dup);
		}
		if (here->file_path)
			here->fd_read = open(here->file_path, O_RDONLY | O_CREAT, 0644);
		if (start_redir(redir, red))
			return (1);
		free(redir->file);
		redir = redir->next;
	}
	return (0);
}

int	redir_isdir(char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	ft_redirect(t_redir *redir, t_env **env_list)
{
	t_here	here;
	t_exec	*ex;
	t_red	red;
	int		pid;

	ex = (t_exec *)redir->cmd;
	if (redirect_loop(redir, &red, &here, env_list))
		return (1);
	pid = fork();
	if (pid == -1)
	{
		free(here.file_path);
		perror("fork");
		g_var.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
		redirect_exec(&red, &here, ex, env_list);
	if (here.file_path)
		unlink(here.file_path);
	free(here.file_path);
	freethis(ex->argv);
	free(ex);
	wait(&g_var.exit_status);
	redir_exit_status();
	return (0);
}
