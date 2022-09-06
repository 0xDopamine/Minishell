/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:10:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/06 12:22:48 by abaioumy         ###   ########.fr       */
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

static	void	heredoc_compare(char *line, char *str, char *ret, t_env *env_list)
{
	if (ft_strncmp(ret, "found", 5) == 0)
	{
		line = heredoc_findenv(line, env_list, EDIT);
		line = ft_strjoin(line, "\n");
		str = ft_strjoin(str, line);
	}
    if (ft_strncmp(ret, "not found", 9) == 0)
		str = ft_strjoin(str, "\n"); 
}

void    heredoc_writefile(char *delimiter, int fd, t_env **env_list)
{
	char	*line;
	char	*ret;
	char	*str;

	line = NULL;
    ret = NULL;
	str = NULL;
	while (true)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
        if (line[0] == '$')
        {
            ret = heredoc_findenv(&line[1], *env_list, FIND);
			heredoc_compare(line, str, ret, *env_list);
        }
		else
		{	
			line = ft_strjoin(line, "\n");
			str = ft_strjoin(str, line);
		}
	}
	ft_putstr_fd(str, NULL, fd);
}