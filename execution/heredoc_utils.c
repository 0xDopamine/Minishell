/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:10:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/18 22:02:56 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

static	char	*heredoc_normalcase(char *line, char *str)
{
	line = ft_strjoin(line, "\n");
	str = ft_strjoin(str, line);
	return (str);
}

static	char	*heredoc_findenv(char *line, t_env *env_list, int n)
{
	if (n == FIND)
	{
		if (line[0] == '?')
			return ("exit");
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
	if (ft_strncmp(ret, "exit", 4) == 0)
	{
		line = ft_strjoin(ft_itoa(g.exit_status), &line[index + 2]);
		line = ft_strjoin(line, "\n");
		str = ft_strjoin(str, line);
	}
	return (str);
}

void	heredoc_writefile(char *delimiter, int fd, t_env **env_list)
{
	t_write	w;

	w.line = NULL;
	w.ret = NULL;
	w.str = NULL;
	w.index = -1;
	while (true)
	{
		w.line = readline(YELLOW"heredoc> " RESET);
		if (!w.line)
			break ;
		if (ft_strcmp(w.line, delimiter) == 0)
			break ;
		w.index = heredoc_findsign(w.line);
		if (w.index != -1)
		{
			w.ret = heredoc_findenv(&w.line[w.index + 1], *env_list, FIND);
			w.str = heredoc_compare(w.line, w.str, w.ret, *env_list);
			w.str = ft_strjoin(heredoc_getstr(w.line), w.str);
		}
		else
			w.str = heredoc_normalcase(w.line, w.str);
	}
	ft_putstr_fd(w.str, NULL, fd);
	free(w.str);
}
