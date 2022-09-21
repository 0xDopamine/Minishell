/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:31:13 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	heredoc_open(char *file_path, t_cmd *cmd, t_env **env_list)
{
	int	pid;
	int	fd_rd;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_var.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
	{
		fd_rd = open(file_path, O_RDONLY | O_CREAT, 0644);
		dup2(fd_rd, STDIN_FILENO);
		ft_exec_nofork((t_exec *)cmd, env_list);
		close(fd_rd);
		exit(1);
	}
	return (0);
}

char	*heredoc_gen_name(int i)
{
	int		fd;
	char	*buffer;
	char	*tmp;
	char	*s;

	s = ft_strdup("0123456789abcdefghijklmnopqrstuvwxyz");
	buffer = (char *)malloc(9);
	buffer[8] = '\0';
	fd = open("/dev/random", O_RDONLY, 0);
	read(fd, buffer, 8);
	while (buffer[i])
	{
		buffer[i] = s[(buffer[i] + 360) % 36];
		i++;
	}
	free(s);
	tmp = buffer;
	buffer = ft_strjoin("/tmp/", buffer);
	free (tmp);
	return (buffer);
}

int	heredoc_create(char *file_path)
{
	int		pid;
	int		fd_creat;

	pid = 0;
	fd_creat = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd_creat < 0)
	{
		ft_putstr_fd("file creation failed\n", NULL, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g_var.exit_status = EXIT_FAILURE;
		return (-1);
	}
	return (fd_creat);
}

int	ft_heredoc(t_here *here, t_redir *redir, t_env **env_list)
{
	int	i;

	i = 0;
	here->file_path = heredoc_gen_name(i);
	here->fd_creat = heredoc_create(here->file_path);
	if (here->fd_creat == -1)
		return (-1);
	here->delimiter = redir->file;
	here->cmd = redir->cmd;
	heredoc_writefile(here->delimiter, here->fd_creat, env_list);
	return (EXIT_SUCCESS);
}
