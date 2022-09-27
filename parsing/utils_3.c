/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:55:10 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 13:57:33 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*findthewae(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PATH=", 5) == 0)
			return (str[i] + 5);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < (int)n)
	{
		str[i] = '\0';
		i++;
	}
}

int	ft_strchr(char s, char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_env_quoted(char **s, char **es, t_env *env_list)
{
	char	*temp;
	char	*q;
	char	*eq;
	char	*res;

	q = *s;
	eq = *es;
	res = ft_strdup("'");
	fetch_quoted(&q, &eq);
	q = ft_join_string(q, eq);
	temp = ft_assign_env(q, env_list);
	res = strjoin_and_free1(res, temp);
	res = strjoin_and_free1(res, "'");
	free(temp);
	free(q);
	return (res);
}

void	ft_line_protection(char	*line)
{
	if (!line)
	{
		free(line);
		ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
		exit(255);
	}
}
