/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:28:35 by codespace         #+#    #+#             */
/*   Updated: 2022/09/25 16:25:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_start_pipe(t_cmd *cmd, int *in, int fds[2], t_env **env_list)
{
	if (cmd->type == PIPE)
		ft_pipes((t_pipe *)cmd, env_list, in);
	else if (cmd->type == EXEC)
	{
		((t_exec *)cmd)->pid = fork();
		if (((t_exec *)cmd)->pid == 0)
		{
            fprintf(stderr, "%d %d", *in, fds[1]);
			dup2(fds[1], 1);
			dup2(*in, 0);
			if (*in != 0)
				close(*in);
			if (fds[0] != 0)
				close(fds[0]);
			if (fds[1] != 1)
				close(fds[1]);
			ft_exec_nofork((t_exec *)cmd, env_list);
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd->type == REDIR)
	{
		if (ft_handle_redirections((t_redir *)cmd, in, &fds[1], env_list) == 0)
			ft_start_pipe(((t_redir *)cmd)->cmd, in, fds, env_list);
	}
}
