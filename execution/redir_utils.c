/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:55:27 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/15 19:05:33 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_redirect_output(t_redir *redir, t_red *red)
{
	printf("file: %s\n", redir->file);
	red->out_fd = open(redir->file, redir->mode, 0644);
	if (red->out_fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int	ft_redirect_input(t_redir *redir, t_red *red)
{
	printf("file: %s\n", redir->file);
	red->in_fd = open(redir->file, redir->mode, 0644);
	if (red->in_fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
		return (-1);
	}
	return (EXIT_SUCCESS);
}
