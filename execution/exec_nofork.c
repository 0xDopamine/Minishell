/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nofork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:47:42 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/11 12:19:59 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execnofork_loop(char *cmd, char **av, char **env)
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
			g.exit_status = EXIT_SUCCESS;
			ft_free_doubleptr(path);
			execve(join, av, env);
			perror("execve");
			free (join);
			return ;
		}
		free(join);
		i++;
	}
	g.exit_status = EXIT_NOTFOUND;
	ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
	ft_free_doubleptr(path);
}

void	ft_exec_nofork(t_exec *line, char **env, t_env **env_list)
{
	char	*cmd;

	if (!line->argv[0] || line->argv[0] == NULL)
	{
		g.exit_status = EXIT_FAILURE;
		return ;
	}
	cmd = ft_strdup(line->argv[0]);
	if (ft_builtins(cmd, line, env_list))
		return ;
	cmd = ft_strjoin("/", cmd);
	execnofork_loop(cmd, line->argv, env);
	exit(EXIT_SUCCESS);
}
