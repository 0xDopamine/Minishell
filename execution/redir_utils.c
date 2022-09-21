/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:55:27 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	start_redir(t_redir *redir, t_red *red)
{
	if (redir->fd == STDIN_FILENO)
	{
		if (ft_redirect_input(redir, red) == -1)
			return (1);
	}
	if (redir->fd == STDOUT_FILENO)
	{
		if (ft_redirect_output(redir, red) == -1)
			return (1);
	}
	return (0);
}

int	ft_redirect_output(t_redir *redir, t_red *red)
{
	if (redir_isdir(redir->file))
	{
		ft_putstr_fd(redir->file, ": is a directory\n", STDERR_FILENO);
		return (-1);
	}
	red->out_fd = open(redir->file, redir->mode, 0644);
	if (red->out_fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g_var.exit_status = EXIT_NOTFOUND;
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int	ft_redirect_input(t_redir *redir, t_red *red)
{
	if (redir_isdir(redir->file))
	{
		ft_putstr_fd(redir->file, ": is a directory\n", STDERR_FILENO);
		return (-1);
	}
	red->in_fd = open(redir->file, redir->mode, 0644);
	if (red->in_fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g_var.exit_status = EXIT_NOTFOUND;
		return (-1);
	}
	return (EXIT_SUCCESS);
}
