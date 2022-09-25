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

int	ft_open_file(t_redir *redir)
{
	int fd;

	if (redir_isdir(redir->file))
	{
		ft_putstr_fd(redir->file, ": is a directory\n", STDERR_FILENO);
		return (-1);
	}
	fd  = open(redir->file, redir->mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

int	ft_handle_redirections(t_redir *redir, int *in, int *out, t_env **env_list)
{
	int		infd_dup;
	t_here	here;

	here.file_path = NULL;
	here.fd_creat = -2;
	infd_dup = dup(0);
	signal(SIGINT, ft_sig_here);
	while (redir)
	{
		if (redir->mode == HEREDOC && !g_var.here_sig)
		{
			if (start_heredoc(&here, redir, infd_dup, env_list) == -1)
			{
				close(infd_dup);
				return (1);
			}
			if (*in != 0)
				close(*in);
			*in  = open(here.file_path, O_RDONLY, 0644);
			if (*in == -1)
				return (-1);
		}
		else if (redir->fd == STDIN_FILENO)
		{
			if (*in != 0)
				close(*in);
			*in = ft_open_file(redir);
			if (*in == -1)
				return (-1);
		}
		else if (redir->fd == STDOUT_FILENO)
		{
			if (*out != 1)
				close(*out);
			*out = ft_open_file(redir);
			if (*out == -1)
				return (-1);
		}
		if (*in == -1 || *out == -1)
		{
			close(infd_dup);
			return (1);
		}
		redir = redir->next;
	}
	signal(SIGINT, ft_sig_handler);
	close(infd_dup);
	return (0);
}	

int	redir_isdir(char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
