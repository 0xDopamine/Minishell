/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:10:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:35 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

static	void	heredoc_normalcase(t_write *w)
{
	char	*tmp;

	tmp = w->line;
	w->line = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = w->str;
	w->str = ft_strjoin(tmp, w->line);
	free(w->line);
	free(tmp);
}

void	heredoc_writefile(char *delimiter, int fd, t_env **env_list)
{
	t_write	w;

	w.line = NULL;
	w.ret = NULL;
	w.str = NULL;
	w.index = -1;
	while (TRUE)
	{
		w.line = readline(YELLOW"heredoc> " RESET);
		if (!w.line)
			break ;
		if (ft_strcmp(w.line, delimiter) == 0)
		{
			free(w.line);
			break ;
		}
		w.index = heredoc_findsign(w.line);
		if (w.index != -1)
			heredoc_specialcase(&w, env_list);
		else
			heredoc_normalcase(&w);
	}
	ft_putstr_fd(w.str, NULL, fd);
	free(w.str);
}
