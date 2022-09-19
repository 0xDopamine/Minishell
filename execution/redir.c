/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/19 17:09:15 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		exit(1);
	}
	if (red->in_fd != -2 && red->in_fd != -1)
		dup2(red->in_fd, STDIN_FILENO);
	if (red->out_fd != -2 && red->out_fd != -1)
		dup2(red->out_fd, STDOUT_FILENO);
	ft_exec_nofork(ex, env_list);
	exit(1);
}

void	ft_sig_here(int signal)
{
	(void)signal;
	close(0);
	g.here_sig = 1;
}

static	int	redirect_loop(t_redir *redir, t_red *red
	, t_here *here, t_env **env_list)
{
	int	infd;

	here->file_path = NULL;
	here->fd_creat = -2;
	red->in_fd = -2;
	red->out_fd = -2;
	infd = dup(0);
	signal(SIGINT, ft_sig_here);
	while (!g.here_sig && redir && redir->mode == HEREDOC)
	{
		if (ft_heredoc(here, redir, env_list) == -1)
		{
			close(infd);
			return (1);
		}
		redir = redir->next;
	}
	if (g.here_sig)
	{
		free(here->file_path);
		signal(SIGINT, ft_sig_handler);
		g.here_sig = 0;
		dup2(infd, 0);
		close(infd);
		return (1);
	}
	close(infd);
	if (here->file_path)
		here->fd_read = open(here->file_path, O_RDONLY | O_CREAT, 0644);
	while (redir && redir->fd == STDIN_FILENO)
	{
		if (ft_redirect_input(redir, red) == -1)
			return (1);
		redir = redir->next;
	}
	while (redir && redir->fd == STDOUT_FILENO)
	{
		if (ft_redirect_output(redir, red) == -1)
			return (1);
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
		perror("fork");
		g.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
		redirect_exec(&red, &here, ex, env_list);
	if (here.file_path)
		unlink(here.file_path);
	free(here.file_path);
	wait(&g.exit_status);
	if (g.exit_status == 256)
		g.exit_status = EXIT_NOTFOUND;
	else
		g.exit_status = EXIT_SUCCESS;
	return (0);
}
