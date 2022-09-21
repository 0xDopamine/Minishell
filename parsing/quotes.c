/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:08:56 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 03:31:56 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	ft_strlen_q(char *q, char *eq)
{
	int		len;
	char	*temp;
	char	*es;

	len = 0;
	temp = q;
	es = eq;
	while (temp++ < es)
		len++;
	return (len);
}

void	fetch_quoted(char **q, char **eq)
{
	char	*s;
	int		tok;

	tok = **q;
	s = *q + 1;
	*q = s;
	while (*s && *s != tok)
		s++;
	if (*s == '\0')
	{
		*q = NULL;
		ft_putstr_fd("Quotes error\n", NULL, STDERR_FILENO);
		g.exit_status = 256;
		return ;
	}
	*eq = s;
}

int	ft_check_quotes(char *s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], "\'\""))
		{
			j = i + 1;
			while (s[j] != s[i] && s[j])
				j++;
			if (s[j] == '\0')
			{
				perror("Quotes error");
				g.exit_status = 256;
				return (0);
			}
			else
				i++;
		}
		else
			i++;
	}
	return (1);
}
