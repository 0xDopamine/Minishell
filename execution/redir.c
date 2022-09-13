/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/13 22:43:56 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int		redir_checkpath(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i+1])
		{
			ft_putstr_fd("ambiguous (amogus) redirect", NULL, STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}
static	int	redir_checkname(char **filename, t_env **env_list)
{
	t_env	*list;
	int		i;

	list = *env_list;
	i = 1;
	while (list)
	{
		if (ft_strcmp(&filename[0][1], list->name) == 0)
		{
			if (redir_checkpath(list->path))
			{
				free (filename[0]);
				filename[0] = ft_strdup(list->path);
				return (0);
			}
			else
				return (1);
		}
		list = list->next;
	}
	return (0);
}

int	ft_redirect(t_redir *redir, t_env **env_list)
{
	int	fd_file;
	t_exec	*ex;
	t_red	red;
	int		pid;

	red.in_fd = -1024;
	red.out_fd = -1024;
	fd_file = 0;
	// ex = (t_exec *)redir->right;
	if (redir->mode == HEREDOC)
		ft_heredoc(env_list, redir->right, redir->file);
	while (redir && redir->fd == STDIN_FILENO)
	{
		printf("file: %s\n", redir->file);
		if (redir_checkname(&(redir->file), env_list) && redir->file[0] == '$')
			return (0);
		fd_file = open(redir->file, redir->mode, 0644);
		red.in_fd = fd_file;
		if (red.in_fd == -1)
		{
			ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			g.exit_status = EXIT_NOTFOUND;
			return (-1);
		}
		ex = (t_exec *)redir->right;
		redir = (t_redir *)redir->left;
	}
	while (redir && redir->fd == STDOUT_FILENO)
	{
		if (redir_checkname(&(redir->file), env_list) && redir->file[0] == '$')
			return (0);
		fd_file = open(redir->file, redir->mode, 0644);
		red.out_fd = fd_file;
		if (red.out_fd == -1)
		{
			ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			g.exit_status = EXIT_NOTFOUND;
			return (-1);
		}
		ex = (t_exec *)redir->right;
		redir = (t_redir *)redir->left;
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
		if (red.in_fd != -1024 && red.in_fd != -1)
			dup2(red.in_fd, STDIN_FILENO);
		if (red.out_fd != -1024 && red.out_fd != -1)
			dup2(red.out_fd, STDOUT_FILENO);
		ft_exec_nofork(ex, env_list);
	}
	wait(&g.exit_status);
	if (g.exit_status == 256)
		g.exit_status = EXIT_NOTFOUND;
	else
		g.exit_status = EXIT_SUCCESS;
	return (0);
}

// void	ft_redirect(t_redir *redir, char **env, t_env **env_list)
// {
// 	int		fd_file;
// 	t_exec	*ex;
// 	t_redir	*redir2;
// 	t_cmd	*cmd;
// 	int		pid;

// 	redir2 = (t_redir *)redir->left;
// 	cmd = (t_cmd *)redir->left;
// 	ex = (t_exec *)redir->right;
// 	// printf("%s\n%s\n", ex->argv[0], ex->argv[1]);
// 	fd_file = open(redir->file, redir->mode, 0644);
// 	if (fd_file < 0)
// 	{
// 		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
// 		ft_putchar_fd('\n', STDERR_FILENO);
// 		g.exit_status = EXIT_NOTFOUND;
// 		return ;
// 	}
// 	if (cmd->type == REDIR && redir2->fd == redir->fd)
// 	{
// 		ft_redirect((t_redir *)redir->left, env, env_list);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		dup2(fd_file, redir->fd);
// 		ft_exec_nofork(ex, env, env_list);
// 		ft_putstr_fd(ex->argv[0], ": command not found\n", STDERR_FILENO);
// 		close(fd_file);
// 		exit(EXIT_FAILURE);
// 	}
// 	close(fd_file);
// 	wait(&g.exit_status);
// 	if (g.exit_status == 256)
// 		g.exit_status = EXIT_NOTFOUND;
// 	else
// 		g.exit_status = EXIT_SUCCESS;
// }
