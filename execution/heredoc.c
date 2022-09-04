/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:31:13 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/04 21:02:17 by mbaioumy         ###   ########.fr       */
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
            {
                printf("found\n");
				return ("found");
            }
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

void	ft_heredoc(t_env **env_list)
{
	char	*line;
	char	*delimiter;
	int		fd;
	char 	*str;
    char    *ret;

	line = NULL;
    ret = NULL;
	str = NULL;
	delimiter = "EOF";
	fd = open(heredoc_gen_name(), O_RDWR | O_CREAT | O_APPEND, 0666);
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
                printf("im here\n");
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
	exit(1);
}