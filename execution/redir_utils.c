/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:55:27 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redirect_input(t_redir *redir, int *in)
{
	if (*in != 0)
		close(*in);
	*in = ft_open_file(redir);
	if (*in == -1)
		return (-1);
	return (0);
}

int	redirect_output(t_redir *redir, int *out)
{
	if (*out != 1)
		close(*out);
	*out = ft_open_file(redir);
	if (*out == -1)
		return (-1);
	return (0);
}

int	ft_open_file(t_redir *redir)
{
	int	fd;

	if (redir_isdir(redir->file))
	{
		ft_putstr_fd(redir->file, ": is a directory\n", STDERR_FILENO);
		return (-1);
	}
	fd = open(redir->file, redir->mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	return (fd);
}
