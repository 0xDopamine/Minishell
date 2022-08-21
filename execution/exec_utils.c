/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:57 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/21 16:56:18 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_check_cmd(t_cmd *cmd, char **env, t_env **env_list)
{
	if (cmd->type == EXEC)
		ft_exec((t_exec *)cmd, env, env_list);
	if (cmd->type == REDIR)
		ft_redirect((t_redir *)cmd, env, env_list);
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
