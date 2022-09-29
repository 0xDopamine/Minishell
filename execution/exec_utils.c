/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:57 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	handle_exec_case(t_cmd *cmd, int *in, t_env **env_list)
{
	int	fds[2];

	fds[0] = 0;
	fds[1] = 1;
	if (ft_ifmybuiltin(((t_exec *)cmd)->argv[0], (t_exec *)cmd, env_list)
		|| ft_ifmybuiltin_up(((t_exec *)cmd)->argv[0]
			, (t_exec *)cmd, env_list))
		return (1);
	ft_start_pipe(cmd, in, fds, env_list);
	return (0);
}

static void	ft_close_fds(int *tmp_in, int *tmp_out)
{
	dup2(*tmp_in, 0);
	dup2(*tmp_out, 1);
	close(*tmp_in);
	close(*tmp_out);
}

static void	ft_dup_fds(int *in, int *out, t_cmd *cmd, t_env **env_list)
{
	dup2(*in, 0);
	dup2(*out, 1);
	if (*in != 0)
		close(*in);
	if (*out != 1)
		close(*out);
	handle_one_command(((t_redir *)cmd)->cmd, env_list);
}

int	handle_one_command(t_cmd *cmd, t_env **env_list)
{
	int	in;
	int	tmp_in;
	int	out;
	int	tmp_out;

	in = 0;
	out = 1;
	if (cmd->type == REDIR)
	{
		tmp_in = dup(0);
		tmp_out = dup(1);
		if (ft_handle_redirections((t_redir *)cmd, &in, &out, env_list) == 0)
			ft_dup_fds(&in, &out, cmd, env_list);
		ft_close_fds(&tmp_in, &tmp_out);
		return (0);
	}
	else
		return (handle_exec_case(cmd, &in, env_list));
	return (0);
}
