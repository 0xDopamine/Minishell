/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:09:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/18 01:17:10 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*ft_join_string(char *q, char *eq)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(1) * ft_strlen_q(q, eq) + 1);
	while (q < eq)
	{
		res[i++] = *q;
		q++;
	}
	res[i] = '\0';
	return (res);
}

void	fetch_string(char **q, char **eq)
{
	char	*s;
	int		tok;

	tok = **q;
	s = *q;
	*q = s;
	while (!ft_strchr(*s, "\'\"") && *s)
		s++;
	*eq = s--;
}

void	fetch_env(char **q, char **eq)
{
	char	*s;

	s = *q;
	while (*s)
	{
		if (ft_strchr(*s, "\'\"") || !ft_isalnum(*s))
			break ;
		s++;
	}
	*eq = s;
}

void	trim_string(char *q)
{
	int		i;
	char	*temp;

	i = 0;
	temp = q;
	while (temp[i])
	{
		if (ft_strchr(temp[i], "\'\""))
			break ;
		i++;
	}
	q[i] = '\0';
}

int	ft_count_dollars(char *q)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (q[i])
	{
		while (q[i] == '$' && q[i])
		{
			i++;
			count++;
			if (q[i] != '$')
				return (count);
		}
		i++;
	}
	return (count);
}
