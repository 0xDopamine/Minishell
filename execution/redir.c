/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/16 02:35:25 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// static int		redir_checkpath(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ' && str[i+1])
// 		{
// 			ft_putstr_fd("ambiguous (amogus) redirect", NULL, STDERR_FILENO);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }
// static	int	redir_checkname(char **filename, t_env **env_list)
// {
// 	t_env	*list;
// 	int		i;

// 	list = *env_list;
// 	i = 1;
// 	while (list)
// 	{
// 		if (ft_strcmp(&filename[0][1], list->name) == 0)
// 		{
// 			if (redir_checkpath(list->path))
// 			{
// 				free (filename[0]);
// 				filename[0] = ft_strdup(list->path);
// 				return (0);
// 			}
// 			else
// 				return (1);
// 		}
// 		list = list->next;
// 	}
// 	return (0);
// }

int	ft_redirect(t_redir *redir, t_env **env_list)
{
	t_here		here;
	t_exec		*ex;
	t_red		red;
	int			pid;
	static int	in;
	static int	out;

	here.file_path = NULL;
	here.fd_creat = -1024;
	red.in_fd = -1024;
	red.out_fd = -1024;
	while (redir && redir->mode == HEREDOC)
	{
		if (ft_heredoc(&here, redir, env_list) == -1)
			return (1);
		redir = (t_redir *)redir->next;
	}
	if (here.file_path)
		here.fd_read = open(here.file_path, O_RDONLY | O_CREAT, 0644);
	if ((redir && redir->fd == STDIN_FILENO))
	{
		ft_redirect_input(redir, &red);
		ex = (t_exec *)redir->cmd;
	}
	if (redir && redir->fd == STDOUT_FILENO)
	{
		ft_redirect_output(redir, &red);
		ex = (t_exec *)redir->cmd;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
	{
		if (here.fd_creat != -1024 && here.fd_creat != -1)
		{
			dup2(here.fd_read, STDIN_FILENO);
			if (red.out_fd != -1024 && red.out_fd != -1)
				dup2(red.out_fd, STDOUT_FILENO);
			ft_exec_nofork((t_exec *)here.cmd, env_list);
			close(here.fd_creat);
			close(here.fd_read);
			exit(1);
		}
		if (in == 0 && red.in_fd != -1024 && red.in_fd != -1)
		{
			printf ("%d && %s\n", in, redir->file);
			dup2(red.in_fd, STDIN_FILENO);
			in++;
		}
		if (out == 0 && red.out_fd != -1024 && red.out_fd != -1)
		{
			dup2(red.out_fd, STDOUT_FILENO);
			out++;
		}
		if (redir->cmd->type == EXEC)
			ft_exec_nofork(ex, env_list);
		else if (redir->cmd->type == REDIR)
			ft_redirect((t_redir*)redir->cmd, env_list);
		exit(1);
	}
	if (here.file_path)
		unlink(here.file_path);
	wait(&g.exit_status);
	if (g.exit_status == 256)
		g.exit_status = EXIT_NOTFOUND;
	else
		g.exit_status = EXIT_SUCCESS;
	return (0);
}
