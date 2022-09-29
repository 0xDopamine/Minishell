/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:53:28 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 20:56:17 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// static	char	*here_exit_found(char *str, char *line, int index)
// {
// 	char	*nbr;
// 	char	*tmp;

// 	nbr = ft_itoa(g_var.exit_status);
// 	line = ft_strjoin(nbr, &line[index + 2]);
// 	free (nbr);
// 	tmp = line;
// 	line = ft_strjoin(tmp, "\n");
// 	free(tmp);
// 	tmp = str;
// 	str = ft_strjoin(tmp, line);
// 	free(line);
// 	free(tmp);
// 	return (str);
// }

// static	char	*heredoc_findenv(char *line, t_env *env_list, int n)
// {
// 	if (n == FIND)
// 	{
// 		if (line[0] == '?')
// 			return ("exit");
// 		while (env_list)
// 		{
// 			if (ft_strcmp(line, env_list->name) == 0)
// 				return ("found");
// 			env_list = env_list->next;
// 		}
// 		return ("not found");
// 	}
// 	while (env_list)
// 	{
// 		if (ft_strcmp(&line[1], env_list->name) == 0)
// 			return (ft_strdup(env_list->path));
// 		env_list = env_list->next;
// 	}
// 	return (NULL);
// }

// static	char	*here_expand_found(char *str, char *line
// 	, t_env *env_list, int index)
// {
// 	char	*tmp;

// 	line = heredoc_findenv(&line[index], env_list, EDIT);
// 	tmp = line;
// 	line = ft_strjoin(tmp, "\n");
// 	free (tmp);
// 	tmp = str;
// 	str = ft_strjoin(tmp, line);
// 	free(line);
// 	free(tmp);
// 	return (str);
// }

// static	char	*heredoc_compare(char *line, char *str
// 	, char *ret, t_env *env_list)
// {
// 	int		index;
// 	char	*tmp;

// 	index = heredoc_findsign(line);
// 	if (ft_strcmp(ret, "found") == 0)
// 		str = here_expand_found(str, line, env_list, index);
// 	if (ft_strcmp(ret, "not found") == 0)
// 	{
// 		tmp = str;
// 		str = ft_strjoin(tmp, "\n");
// 		free(tmp);
// 	}
// 	if (ft_strcmp(ret, "exit") == 0)
// 		str = here_exit_found(str, line, index);
// 	return (str);
// }

// void	heredoc_specialcase(t_write *w, t_env **env_list)
// {
// 	char	*tmp;
// 	char	*tmp2;

// 	w->ret = heredoc_findenv(&w->line[w->index + 1], *env_list, FIND);
// 	tmp2 = heredoc_compare(w->line, w->str, w->ret, *env_list);
// 	tmp = (w->line);
// 	w->line = heredoc_getstr(tmp);
// 	free(tmp);
// 	tmp = w->line;
// 	w->str = ft_strjoin(tmp, tmp2);
// 	free (tmp2);
// 	free(tmp);
// }
