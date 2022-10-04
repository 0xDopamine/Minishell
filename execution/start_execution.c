/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:28:35 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/25 19:49:20 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	void	ft_dup_fds(int *in, int *read_fd, int *write_fd)
{
	dup2(*write_fd, 1);
	dup2(*in, 0);
	if (*in != 0)
		close(*in);
	if (*read_fd != 0)
		close(*read_fd);
	if (*write_fd != 1)
		close(*write_fd);
}

void	ft_start_pipe(t_cmd *cmd, int *in, int fds[2], t_env **env_list)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == PIPE)
		ft_pipes((t_pipe *)cmd, env_list, in);
	else if (cmd->type == EXEC)
	{
		((t_exec *)cmd)->pid = fork();
		if (((t_exec *)cmd)->pid == -1)
		{
			perror("fork");
			g_var.exit_status = EXIT_FAILURE;
			return ;
		}
		if (((t_exec *)cmd)->pid == 0)
		{
			ft_dup_fds(in, &fds[0], &fds[1]);
			ft_exec_nofork((t_exec *)cmd, env_list);
			exit(0);
		}
	}
	else if (cmd->type == REDIR)
	{
		if (ft_handle_redirections((t_redir *)cmd, in, &fds[1], env_list) == 0)
			ft_start_pipe(((t_redir *)cmd)->cmd, in, fds, env_list);
	}
}
