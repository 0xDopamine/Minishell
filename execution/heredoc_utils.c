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

static	void	heredoc_norme(t_write *w, char *ret)
{
	free(w->line);
	w->str = strjoin_and_free(w->str, ret);
	w->str = strjoin_and_free1(w->str, "\n");
}

static	void	init_vars(t_write *w)
{
	w->line = NULL;
	w->ret = NULL;
	w->str = NULL;
	w->index = -1;
}

static void	heredoc_normalcase(t_write *w)
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
	char	*ret;

	init_vars(&w);
	while (TRUE)
	{
		w.line = readline(YELLOW"heredoc> " RESET);
		if (!w.line || (!delimiter && ft_strlen(w.line) == 0))
		{
			free(w.line);
			break ;
		}
		if (w.line && ft_strcmp(w.line, delimiter) == 0)
		{
			free(w.line);
			break ;
		}
		ret = heredoc_findsign(w.line, *env_list);
		if (ret)
			heredoc_norme(&w, ret);
		else
			heredoc_normalcase(&w);
	}
	ft_putstr_fd(w.str, NULL, fd);
	free(w.str);
}
