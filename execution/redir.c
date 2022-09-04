/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/04 16:02:17 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

static char *heredoc_findenv(char *line, t_env *env_list, int n)
{
	if (n == FIND)
	{
		while (env_list)
		{
			if (ft_strncmp(line, env_list->name, ft_strlen(env_list->name)) == 0)
				return ("found");
			env_list = env_list->next;
		}
		return (NULL);
	}
	while (env_list)
	{
		if (ft_strncmp(&line[1], env_list->name, ft_strlen(env_list->name)) == 0)
			return (env_list->path);
		env_list = env_list->next;
	}
	return (NULL);
}

static char *heredoc_gen_name(void)
{
	int		fd;
    char	*buffer;
    int		i;
    char	*s;
	
	s = ft_strdup("0123456789abcdefghijklmnopqrstuvwxyz");
	i = 0;
    buffer = (char *)malloc(9);
	buffer[8] = '\0';
	fd = open("/dev/random", O_RDONLY, 0);
    read(fd, buffer, 8);
    while (buffer[i])
    {
        buffer[i] = s[(buffer[i] + 360) % 36];
        i++;
    }
	return (ft_strjoin("/tmp/", buffer));
}

void	ft_heredoc(t_env **env_list)
{
	char	*line;
	char	*delimiter;
	int		fd;
	char 	*str;

	line = NULL;
	str = NULL;
	delimiter = "EOF";
	fd = open(heredoc_gen_name(), O_RDWR | O_CREAT | O_APPEND, 0666);
	while (true)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		if (heredoc_findenv(line, *env_list, FIND))
		{
			line = heredoc_findenv(line, *env_list, EDIT);
			line = ft_strjoin(line, "\n");
			str = ft_strjoin(str, line);
		}
		else
		{	
			line = ft_strjoin(line, "\n");
			str = ft_strjoin(str, line);
		}
	}
	ft_putstr_fd(str, NULL, fd);
	exit(1);
}

void	ft_redirect(t_redir *redir, char **env, t_env **env_list)
{
	int		fd_file;
	t_exec	*ex;
	t_redir	*redir2;
	t_cmd	*cmd;
	int		pid;

	redir2 = (t_redir *)redir->left;
	cmd = (t_cmd *)redir->left;
	ex = (t_exec *)redir->right;
	// ft_heredoc(env_list);
	fd_file = open(redir->file, redir->mode, 0644);
	if (fd_file < 0)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
		return ;
	}
	if (cmd->type == REDIR)
	{
		printf("hello\n");
		ft_redirect((t_redir *)redir->left, env, env_list);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		dup2(fd_file, redir->fd);
		ft_exec_nofork(ex, env, env_list);
		ft_putstr_fd(ex->argv[0], ": command not found\n", STDERR_FILENO);
		close(fd_file);
		exit(EXIT_FAILURE);
	}
	close(fd_file);
	wait(&g.exit_status);
	if (g.exit_status == 256)
		g.exit_status = EXIT_NOTFOUND;
	else
		g.exit_status = EXIT_SUCCESS;
}
