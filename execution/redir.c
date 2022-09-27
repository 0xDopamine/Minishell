/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:21:56 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	start_redir(t_redir *redir, int *in, int *out, int *infd_dup)
{
	if (redir->fd == STDIN_FILENO && redir->mode != HEREDOC)
	{
		if (redirect_input(redir, in) == -1)
			return (1);
	}
	else if (redir->fd == STDOUT_FILENO && redir->mode != HEREDOC)
	{
		printf("hello\n");
		if (redirect_output(redir, out) == -1)
			return (1);
	}
	if (*in == -1 || *out == -1)
	{
		close(*infd_dup);
		return (1);
	}
	return (0);
}

static	void	init_vars(t_here *here, int *infd_dup)
{
	here->file_path = NULL;
	here->fd_creat = -2;
	*infd_dup = dup(0);
	signal(SIGINT, ft_sig_here);
}

int	ft_handle_redirections(t_redir *redir, int *in, int *out, t_env **env_list)
{
	int		infd_dup;
	t_here	here;

	init_vars(&here, &infd_dup);
	while (redir)
	{
		if (redir->mode == HEREDOC && !g_var.here_sig)
		{
			if (start_heredoc(&here, redir, infd_dup, env_list) == -1)
				return (close(infd_dup) * 0 + 1);
			if (*in != 0)
				close(*in);
			*in = open(here.file_path, O_RDONLY, 0644);
			if (*in == -1)
				return (-1);
		}
		if (start_redir(redir, in, out, &infd_dup))
			return (EXIT_FAILURE);
		redir = redir->next;
	}
	signal(SIGINT, ft_sig_handler);
	return (close(infd_dup) * 0);
}	

int	redir_isdir(char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
