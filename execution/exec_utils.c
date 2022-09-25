/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:57 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_isdir(char *cmd)
{
	struct stat	path_stat;

	printf("cmd: %s\n", cmd);
	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void		handle_one_command(t_cmd *cmd, t_env **env_list)
{
	int			in;
	int			out;

	in = 0;
	out = 1;
	if (cmd->type == REDIR)
	{
		const int	tmp_in = dup(0);
		const int	tmp_out = dup(1);
		if (ft_handle_redirections((t_redir *)cmd, &in, &out, env_list) == 0)
		{
			dup2(in, 0);
			dup2(out, 1);
			if (in != 0)
				close(in);
			if (out != 1)
				close(out);
			handle_one_command(((t_redir *)cmd)->cmd, env_list);
		}
		dup2(tmp_in, 0);
		dup2(tmp_out, 1);
		close(tmp_in);
		close(tmp_out);
	} else {
		if (ft_ifmybuiltin(((t_exec *)cmd)->argv[0], (t_exec *)cmd, env_list)
			|| ft_ifmybuiltin_up(((t_exec *)cmd)->argv[0], (t_exec *)cmd, env_list))
			return;
		int fds[2] = {0, 1};
		ft_start_pipe(cmd, &in, fds, env_list);
	}
}

void	ft_check_cmd(t_cmd *cmd, t_env **env_list)
{
	int	fds[2] = {0, 1};
	int in = 0;

	if (cmd->type != PIPE)
	{
		handle_one_command(cmd, env_list);
		return ;
	}
	ft_start_pipe(cmd, &in, fds, env_list);
	if (fds[1] != 1)
		close(fds[1]);
	if (in != 0)
		close(in);

}
