/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:47:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/15 15:20:12 by abaioumy         ###   ########.fr       */
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
	// else
		// ft_putstr_fd("command not found\n", STDERR_FILENO);
}

void	ft_exec(t_exec *line, char **env, t_env **env_list)
{
	char	**path;
	char	*cmd;
	int		i;
	int		pid;
	char	*join;

	i = 0;
	join = NULL;
	if (!line->argv[0])
		return ;
	cmd = ft_strdup(line->argv[0]);
	if (ft_builtins(cmd, line, env_list))
		return ;
	path = ft_find_path();
	cmd = ft_strjoin("/", cmd);
	pid = fork();
	if (pid < 0)
	{
		ft_free_doubleptr(path);
		perror("fork");
		exit(1);
	}
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			if (pid == 0)
			{
				ft_free_doubleptr(path);
				execve(join, line->argv, env);
				perror("execve");
				break ; 
			}
		}
		free(join);
		i++;
	}
	i = 0;
	ft_free_doubleptr(path);
	free(cmd);
	wait(&g.exit_status);
	return ;
}
