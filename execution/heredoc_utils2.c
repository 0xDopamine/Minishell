/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:20:33 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 20:21:55 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	start_heredoc(t_here *here, t_redir *redir, int infd_dup, t_env **env_list)
{
	if (ft_heredoc(here, redir, env_list) == -1)
	{

		close(infd_dup), printf("%s:%d ---> %d\n", __FILE__, __LINE__, infd_dup);
		return 1;
	}
	if (g_var.here_sig)
		return (ft_here_signal(infd_dup));
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
	while (str[i] != '$' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	heredoc_findsign(char *str)
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
