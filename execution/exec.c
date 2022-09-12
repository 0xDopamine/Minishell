/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:47:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/12 14:07:48 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_checkcmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

static	void	exec_loop(char *cmd, char **av, char **env)
{
	char	*join;
	char	*s;

	s = NULL;
	if (exec_isdir(cmd) || ft_strcmp(cmd, getcwd(s, PATH_MAX)) == 0)
	{
		free(s);
		ft_putstr_fd(cmd, ": is a directory\n", STDERR_FILENO);
		g.exit_status = 126;
		return ;
	}
	free(s);
	if (exec_checkcmd_fork(cmd, av, env) == -1)
		return ;
	join = exec_ifaccess(cmd);
	if (join != NULL)
	{
		if (exec_cmdpath(join, env, av) == -1)
			return ; 
		free(join);
	}
	g.exit_status = EXIT_SUCCESS;
	if (wait(&g.exit_status) < 0)
	{
		ft_putstr_fd(&cmd[1], ": command not found\n", STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
	}
}

void	ft_exec(t_exec *line, t_env **env_list)
{
	char	*cmd;
	char	**my_env;

	if (!line->argv[0])
		return ;
	my_env = ft_myenv(*env_list);
	cmd = ft_strdup(line->argv[0]);
	if (!cmd)
		return ;
	if (ft_builtins(cmd, line, env_list))
		return ;
	if (!exec_checkcmd(cmd))
		cmd = ft_strjoin("/", cmd);
	exec_loop(cmd, line->argv, my_env);
	free(cmd);
	return ;
}