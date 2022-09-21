/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:53:28 by abaioumy         #+#    #+#             */
/*   Updated: 2022/09/21 20:56:17 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		line = ft_strjoin(ft_itoa(g_var.exit_status), &line[index + 2]);
		line = ft_strjoin(line, "\n");
		str = ft_strjoin(str, line);
	}
	return (str);
}

void	heredoc_specialcase(t_write *w, t_env **env_list)
{
	w->ret = heredoc_findenv(&w->line[w->index + 1], *env_list, FIND);
	w->str = heredoc_compare(w->line, w->str, w->ret, *env_list);
	w->str = ft_strjoin(heredoc_getstr(w->line), w->str);
}
