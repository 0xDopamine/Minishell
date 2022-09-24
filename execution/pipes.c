/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:32:15 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	void	access_loop(char *cmd)
{
	char	*join;
	char	**path;
	int		i;

	i = 0;
	path = ft_find_path();
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			ft_free_doubleptr(path);
			g_var.exit_status = EXIT_SUCCESS;
			return ;
		}
		free(join);
		i++;
	}
	ft_free_doubleptr(path);
	g_var.exit_status = EXIT_NOTFOUND;
}

void	pipes_access(t_exec *line)
{
	char	*cmd;
	char	*tmp;

	if (!line->argv[0])
		return ;
	cmd = ft_strdup(line->argv[0]);
	if (exec_checkcmd(cmd))
	{
		free(cmd);
		g_var.exit_status = EXIT_SUCCESS;
		return ;
	}
	tmp = ft_strjoin("/", cmd);
	access_loop(cmd);
	free (cmd);
	free (tmp);
}


int	ft_open_file(t_redir *redir)
{
	int fd;

	if (redir_isdir(redir->file))
	{
		ft_putstr_fd(redir->file, ": is a directory\n", STDERR_FILENO);
		return (-1);
	}
	fd  = open(redir->file, redir->mode, 0644), printf("%s:%d --> %d\n", __FILE__, __LINE__, 	fd); // TOREMOVE
	if (fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

int		ft_handle_redirections(t_redir *redir, int *in, int *out, t_env **env_list)
{
	int		infd_dup;
	t_here	here;

	here.file_path = NULL;
	here.fd_creat = -2;
	infd_dup = dup(0);
	signal(SIGINT, ft_sig_here);
	while (redir)
	{
		printf("prr\n");
		if (redir->mode == HEREDOC && !g_var.here_sig)
		{
			if (start_heredoc(&here, redir, infd_dup, env_list) == -1)
			{
				close(infd_dup), printf("%s:%d ---> %d\n", __FILE__, __LINE__, infd_dup);;
				return (1);
			}
			if (*in != 0)
				close(*in), printf("%s:%d ---> %d\n", __FILE__, __LINE__, *in);
			*in  = open(here.file_path, O_RDONLY, 0644), printf("%s:%d --> %d\n", __FILE__, __LINE__, 			*in); // TOREMOVE
		}
		else if (redir->fd == STDIN_FILENO)
		{
			if (*in != 0)
				close(*in), printf("%s:%d ---> %d\n", __FILE__, __LINE__, *in);
			*in = ft_open_file(redir);
		}
		else if (redir->fd == STDOUT_FILENO)
		{
			if (*out != 1)
				close(*out), printf("%s:%d ---> %d\n", __FILE__, __LINE__, *out);
			*out = ft_open_file(redir);
		}
		if (*in == -1 || *out == -1)
		{
			close(infd_dup), printf("%s:%d ---> %d\n", __FILE__, __LINE__, infd_dup);;
			return (1);
		}
		redir = redir->next;
	}
	signal(SIGINT, ft_sig_handler);
	close(infd_dup), printf("%s:%d ---> %d\n", __FILE__, __LINE__, infd_dup);
	return (0);
}	

void	dispatch_pipe_node(t_cmd *cmd, int *in, int fds[2], t_env **env_list)
{
	if (cmd->type == PIPE)
		ft_pipes((t_pipe *)cmd, env_list, in);
	else if (cmd->type == EXEC)
	{
		((t_exec *)cmd)->pid = fork();
		if (((t_exec *)cmd)->pid == 0) // check if return == -1
		{
			dup2(fds[1], 1);
			dup2(*in, 0);
			if (in != 0)
				close(*in), printf("%s:%d ---> %d\n", __FILE__, __LINE__, *in);
			if (fds[0] != 0)
				close(fds[0]), printf("%s:%d ---> %d\n", __FILE__, __LINE__, fds[0]);
			if (fds[1] != 1)
				close(fds[1]), printf("%s:%d ---> %d\n", __FILE__, __LINE__, fds[1]);
			ft_exec_nofork((t_exec *)cmd, env_list);
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd->type == REDIR)
	{
		// TODO: change the in and fds using redirect linked list
		if (ft_handle_redirections((t_redir *)cmd, in, &fds[1], env_list) == 0)
		{
			printf("in=%d out=%d\n", *in, fds[1]);
			dispatch_pipe_node(((t_redir *)cmd)->cmd, in, fds, env_list);
		}
		// maybe we should close in if not == 0
	}
}

void	ft_pipes(t_pipe *pipes, t_env **env_list, int *in)
{
	int	fds[2];

	pipe(fds);
	dispatch_pipe_node(pipes->left, in, fds, env_list);
	close(fds[1]), printf("%s:%d ---> %d\n", __FILE__, __LINE__, fds[1]);
	dispatch_pipe_node(pipes->right, &fds[0], (int[2]){0, 1}, env_list);
	close(fds[0]), printf("%s:%d ---> %d\n", __FILE__, __LINE__, fds[0]);
	// wait(NULL);
	// wait(NULL);
}

