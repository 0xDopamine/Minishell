/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/14 22:12:31 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <readline/readline.h>

int	lexer(char **env, char **token, t_simple_cmd *cmd)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (token[i][0] == '|')
		{
			handle_pipes(env, token, cmd);
			return 0;
		}
	}
	return 1;
}

void	child_process(char **env, t_simple_cmd *cmd)
{
	dup2(cmd->fd[1], 1);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	execute(env, cmd);
}

void	handle_pipes(char **env, char **token, t_simple_cmd *cmd)
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

void	print_command(t_simple_cmd *cmd)
{
	int	i;
	
	i = 0;
	while (cmd->args[i])
	{
		printf("%s\n", cmd->args[i]);
		i++;
	}
}

void	execute(char **env, t_simple_cmd *cmd)
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

void	*parse(char **env, char *line)
{
	int				i;
	char			**token;
	char			*temp;
	t_simple_cmd	*retrieve;

	i = 0;
	token = ft_calloc(sizeof(char *), 3);
	token = ft_split(line, ' ');
	retrieve = ft_calloc(sizeof(t_cmd) * 100000 + sizeof(char *), 1);
	retrieve->args = token;
	retrieve->name = ft_strdup(token[0]);
	if (lexer(env, token, retrieve))
		execute(env, retrieve);
	return 0;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	size_t	capacity;
	t_cmd	*cmd;

	line = NULL;
	capacity = 0;
	cmd = malloc(sizeof(t_cmd));
	line = readline("$>");
	parse(env, line);
	//print_command(cmd->simpleCommand);
	return 0;
}