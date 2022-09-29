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

char	*heredoc_getstr(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	if (str[0] == '$')
		return (NULL);
	ret = (char *)malloc(ft_strlen_char(str, '$') + 1);
	if (!ret)
		return (NULL);
	while (str[i] != '$' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*heredoc_findsign(char *str, t_env *env_list)
{
	int		i;
	char	*eq;
	char	*res;
	char	tok;

	i = 0;
	tok = 0;
	eq = NULL;
	res = NULL;
	while (str[i])
	{
		if (ft_strchr(str[i], "\'\""))
			tok = str[i++];
		if (str[i] == '$' && !tok)
		{
			fetch_env(&str + i, &eq);
			res = ft_join_string(str, eq);
			res = ft_assign_env(res, env_list);
		}
		else if (str[i] == '$' && tok)
		{
			res[0] = tok;
			res = ft_join_string(str + i, eq);
			res = strjoin_and_free(res, ft_assign_env(res, env_list));
			res = strjoin_and_free1(res, &tok);
			return (res);
		}
		i++;
	}
	return (res);
}
