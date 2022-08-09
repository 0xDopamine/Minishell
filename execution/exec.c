/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:47:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/09 16:08:24 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
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

void	ft_exec(t_exec *line, char **env, t_env **env_list)
{
	char **path;
	char *cmd;
	int	i;
	int pid;

	i = 0;
	if (!line->argv[0])
		return ;
	path = ft_find_path();
	cmd = ft_strdup(line->argv[0]);
	if (ft_builtins(cmd, line, env_list))
		return ;
	cmd = ft_strjoin("/", cmd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	i = 0;
	if (pid == 0)
	{
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
	}
	wait(&g.exit_status);
	return ;
}