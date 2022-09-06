/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:31:13 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/06 11:56:27 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

// static	void	heredoc_exec(t_exec *ex, char **env, t_env **env_list)
// {
// 	int	i;
// 	char	**av;
// 	char 	*cmd;

// 	i = 0;
// 	if (!ex->argv[0])
// 		return ;
// 	cmd = ft_strdup(ex->argv[0]);
// 	printf("cmd: %s\n", ex->argv[0]);
// 	av = (char **)malloc(sizeof(char *) * 2);
// 	av[0] = ft_strdup(ex->argv[0]);
// 	av[1] = NULL;
// 	if (ft_builtins(cmd, ex, env_list))
// 		return ;
// 	cmd = ft_strjoin("/", cmd);
// 	execnofork_loop(cmd, av, env);
// }

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
		return ("not found");
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
	free(s);
	return (ft_strjoin("/tmp/", buffer));
}

void	ft_heredoc(t_env **env_list, t_cmd *cmd, char **env, char *delimiter)
{
	char	*line;
	char	*file_path;
	int		fd_cr;
	int		fd_rd;
	char 	*str;
    char    *ret;
	int		pid;

	(void )env;
	file_path = heredoc_gen_name();
	line = NULL;
    ret = NULL;
	str = NULL;
	pid = 0;
	fd_cr = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd_cr < 0)
	{
		ft_putstr_fd("file creation failed\n", NULL, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_FAILURE;
		return ;
	}
	while (true)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
        if (line[0] == '$')
        {
            ret = heredoc_findenv(&line[1], *env_list, FIND);
		    if (ft_strncmp(ret, "found", 5) == 0)
		    {
			    line = heredoc_findenv(line, *env_list, EDIT);
			    line = ft_strjoin(line, "\n");
			    str = ft_strjoin(str, line);
		    }
            if (ft_strncmp(ret, "not found", 9) == 0)
			    str = ft_strjoin(str, "\n"); 
        }
		else
		{	
			line = ft_strjoin(line, "\n");
			str = ft_strjoin(str, line);
		}
	}
	ft_putstr_fd(str, NULL, fd_cr);
	if (cmd->type == EXEC)
	{
		// printf("hello\n");
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
