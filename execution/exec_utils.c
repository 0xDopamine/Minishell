/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:57 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/11 12:21:42 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_isdir(char *cmd)
{
	struct stat	path_stat;

	stat(&cmd[2], &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void	ft_check_cmd(t_cmd *cmd, char **env, t_env **env_list)
{
	if (cmd->type == EXEC)
		ft_exec((t_exec *)cmd, env, env_list);
	if (cmd->type == REDIR)
		if (ft_redirect((t_redir *)cmd, env, env_list) == -1)
			return ;
	if (cmd->type == PIPE)
		ft_pipes((t_pipe *)cmd, env, env_list);
}

char	*exec_ifaccess(char *cmd)
{
	char	**path;
	char	*join;
	int		i;

	i = 0;
	path = ft_find_path();
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			ft_free_doubleptr(path);
			g.exit_status = EXIT_SUCCESS;
			return (join);
		}
		free(join);
		i++;
	}
	return (NULL);
}
