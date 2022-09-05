/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:31:13 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/05 12:33:00 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

// static	void	heredoc_exec(t_exec *ex, char **env, char *file, t_env **env_list)
// {
// 	int	i;
// 	char	**av;
// 	char 	*cmd;

// 	i = 0;
// 	if (ft_builtins(cmd, ex, env_list))
// 		return ;
// 	cmd = ft_strjoin("/", cmd);
// 	execnofork_loop(cmd, ex->argv, env);
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
	return (ft_strjoin("/tmp/", buffer));
}

void	ft_heredoc(t_env **env_list, t_cmd *cmd, char **env)
{
	char	*line;
	char	*delimiter;
	char	*file_path;
	int		fd;
	char 	*str;
    char    *ret;
	int		pid;

	file_path = heredoc_gen_name();
	line = NULL;
    ret = NULL;
	str = NULL;
	pid = 0;
	delimiter = "EOF";
	fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
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
	ft_putstr_fd(str, NULL, fd);
	if (cmd->type == EXEC)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd, STDIN_FILENO);
			ft_exec_nofork((t_exec *)cmd, env, env_list);
			close(fd);
			// heredoc_exec((t_exec *)cmd, env, file_path, env_list);
			exit(1);
		}

	}
	unlink(file_path);
}
