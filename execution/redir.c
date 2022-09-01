/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/01 18:08:36 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

// void	ft_heredoc(void)
// {
// 	char	*line;
// 	char	*delimiter;
// 	int		fd;
// 	char *str;

// 	line = NULL;
// 	str = ft_strdup("");
// 	delimiter = "EOF";
// 	fd = open("/tmp/test", O_RDWR | O_CREAT | O_APPEND, 0666);
// 	while (true)
// 	{
// 		line = readline("heredoc> ");
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
// 			break ;
// 		line = ft_strjoin(line, "\n");
// 		str = ft_strjoin(str, line);
// 	}
// 	ft_putstr_fd(str, NULL, fd);
// 	exit(1);
// }

void	ft_redirect(t_redir *redir, char **env, t_env **env_list)
{
	int		fd_file;
	t_exec	*ex;
	int		pid;

	// ft_heredoc();
	ex = (t_exec *)redir->cmd;
	fd_file = open(redir->file, redir->mode, 0644);
	if (fd_file < 0)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
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
