/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:44:20 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/16 18:45:02 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	child_process(char **env, t_list *cmd)
{
	dup2(cmd->fd[1], 1);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	execute(env, cmd);
}

void	handle_pipes(char **env, char **token, t_list *cmd)
{
	if (pipe(cmd->fd) < 0)
		perror("Pipe Error");
	int	pid1 = fork();
	if (pid1 == -1)
		perror("Fork Error");
	if (pid1 == 0)
		child_process(env, cmd);
	dup2(cmd->fd[0], 0);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}

void	execute(char **env, t_list *cmd)
{
	char	*path;
	char	*arg;

	int	i = -1;
	path = findthewae(env);
	if (!path)
		return (perror("PATH_Error"));
	char **cmdpaths = ft_split(path, ':');
	char **cmda = cmd->args;
	if (cmd->args[0][0] == '/')
	{
		if (access(cmd->args[0], X_OK) == 0)
			if (!execve(cmd->args[0], cmda, env))
				write(2, "Execution Error", 13);
	}
	while (cmdpaths[++i])
	{
		arg = ft_strjoin(cmdpaths[i], "/");
		arg = ft_strjoin(arg, cmd->args[0]);
		if (access(arg, X_OK) == 0)
			if (!execve(arg, cmda, env))
				write(2, "Execution Error", 13);
	}
	//error_handling(cmd);
	exit(1);
}