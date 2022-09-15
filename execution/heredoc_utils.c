/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:10:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/15 19:40:56 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

static	int	ft_strlen_char(char *str, char ch)
{
	unsigned int	len;

	len = 0;
	while (str[len] != ch && str[len])
		len++;
	return (len);
}

static	char	*heredoc_getstr(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(ft_strlen_char(str, '$') + 1);
	if (str[0] == '$')
		return (NULL);
	while (str[i] != '$' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static	int	heredoc_findsign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

static	char	*heredoc_findenv(char *line, t_env *env_list, int n)
{
	if (n == FIND)
	{
		while (env_list)
		{
			if (ft_strncmp(line, env_list->name
					, ft_strlen(env_list->name)) == 0)
				return ("found");
			env_list = env_list->next;
		}
		return ("not found");
	}
	while (env_list)
	{
		if (ft_strncmp(&line[1], env_list->name
				, ft_strlen(env_list->name)) == 0)
			return (env_list->path);
		env_list = env_list->next;
	}
	return (NULL);
}

static	char	*heredoc_compare(char *line, char *str
	, char *ret, t_env *env_list)
{
	int	index;

	index = heredoc_findsign(line);
	if (ft_strncmp(ret, "found", 5) == 0)
	{
		line = heredoc_findenv(&line[index], env_list, EDIT);
		line = ft_strjoin(line, "\n");
		str = ft_strjoin(str, line);
	}
	if (ft_strncmp(ret, "not found", 9) == 0)
		str = ft_strjoin(str, "\n");
	return (str);
}

void	heredoc_writefile(char *delimiter, int fd, t_env **env_list)
{
	char	*line;
	char	*ret;
	char	*str;
	int		index;

	line = NULL;
	ret = NULL;
	str = NULL;
	index = -1;
	while (true)
	{
		line = readline(YELLOW"heredoc> " RESET);
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		index = heredoc_findsign(line);
		if (index != -1)
		{
			ret = heredoc_findenv(&line[index + 1], *env_list, FIND);
			str = heredoc_compare(line, str, ret, *env_list);
			str = ft_strjoin(heredoc_getstr(line), str);
		}
		else
		{	
			line = ft_strjoin(line, "\n");
			str = ft_strjoin(str, line);
		}
	}
	ft_putstr_fd(str, NULL, fd);
}
