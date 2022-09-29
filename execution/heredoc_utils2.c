/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:20:33 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 20:21:55 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_copy_char(char *res, char tok)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)malloc(ft_strlen(res) + 3);
	while (res[i])
	{
		ret[i] = res[i];
		i++;
	}
	free(res);
	ret[i++] = tok;
	ret[i] = '\0';
	return (ret);
}

int	start_heredoc(t_here *here, t_redir *redir, int infd_dup, t_env **env_list)
{
	if (ft_heredoc(here, redir, env_list) == -1)
	{
		free(here->file_path);
		close(infd_dup);
		return (1);
	}
	return (0);
}

int	ft_strlen_char(char *str, char ch)
{
	unsigned int	len;

	len = 0;
	while (str[len] != ch && str[len])
		len++;
	return (len);
}

void	heredoc_fetch_quoted(char **q, char **eq)
{
	char	*s;
	int		tok;

	tok = **q;
	s = NULL;
	if (*q + 1 != 0)
		s = *q + 1;
	else if (!(*q + 1))
	{
		*q = s;
		return ;
	}
	*q = s;
	while (*s && *s != tok)
		s++;
	*eq = s;
}

char	*heredoc_findsign(char *str, t_env *env_list)
{
	int		i;
	char	*eq;
	char	*res;
	char	tok;

	i = -1;
	tok = 0;
	eq = NULL;
	res = NULL;
	while (str[++i])
	{
		if (ft_strchr(str[i], "\'\""))
		{
			tok = str[i];
			heredoc_fetch_quoted(&str, &eq);
		}
		if (str[i] == '$')
		{
			if (tok && !ft_strchr(str[i], "\'\""))
				return (expand_heredoc_q(str, eq, tok, env_list));
			else
				return (expand_heredoc_nq(str, eq, env_list));
		}
	}
	return (res);
}
