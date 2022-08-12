/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:41:18 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/11 18:59:21 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void    ft_exec_nofork(t_exec *line, char **env, t_env **env_list)
{
	char	**path;
	char	*cmd;
	int		i;

	i = 0;
	if (!line->argv[0])
		return ;
	path = ft_find_path();
	cmd = ft_strdup(line->argv[0]);
	if (ft_builtins(cmd, line, env_list))
		return ;
	cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		if (access(ft_strjoin(path[i], cmd), X_OK) == 0)
		{
			execve(ft_strjoin(path[i], cmd), line->argv, env);
			perror("execve");
			break ;
		}
		i++;
	}
	return ;
}