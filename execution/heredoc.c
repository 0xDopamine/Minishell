/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:31:13 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/06 12:22:50 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	free(s);
	return (ft_strjoin("/tmp/", buffer));
}

void	ft_heredoc(t_env **env_list, t_cmd *cmd, char **env, char *delimiter)
{
	char	*file_path;
	int		fd_cr;
	int		fd_rd;
	int		pid;

	file_path = heredoc_gen_name();
	pid = 0;
	fd_cr = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd_cr < 0)
	{
		ft_putstr_fd("file creation failed\n", NULL, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_FAILURE;
		return ;
	}
	heredoc_writefile(delimiter, fd_cr, env_list);
	if (cmd->type == EXEC)
	{
		pid = fork();
		if (pid == 0)
		{
			fd_rd = open(file_path, O_RDONLY | O_CREAT, 0644);
			dup2(fd_rd, STDIN_FILENO);
			ft_exec_nofork((t_exec * )cmd, env, env_list);
			close(fd_rd);
			close(fd_cr);
			exit(1);
		}

	}
	close(fd_cr);
	wait(NULL);
	unlink(file_path);
}
