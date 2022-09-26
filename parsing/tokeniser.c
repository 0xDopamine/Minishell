/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:31:01 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/25 20:35:30 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	next(char **ps, char *toks)
{
	char	*s;

	s = *ps;
	while (s && ft_strchr(*s, " \t\r\v\n\f"))
		s++;
	*ps = s;
	return (*s && ft_strchr(*s, toks));
}

int	is_symbol(char *str)
{
	char	*symbols;
	char	*temp;
	int		i;
	int		j;

	symbols = ft_strdup("<>|");
	temp = symbols;
	i = 0;
	while (str[i])
	{
		j = 0;
		symbols = temp;
		while (symbols[j])
		{
			if (str[i] == symbols[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_token_redir(char **s, int tok)
{
	char	*p;

	p = *s;
	if (*p == '<')
	{
		p++;
		if (*p == '<')
			tok = 'H';
		p++;
	}
	else if (*p == '>')
	{
		p++;
		if (*p == '>')
		{
			tok = 'A';
			p++;
		}
	}
	*s = p;
	return (tok);
}

void	ft_skip_whitespace(char **ps)
{
	char	*s;

	s = *ps;
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	*ps = s;
}

int	get_token(char **ps, char **q)
{
	char	*s;
	int		tok;

	s = *ps;
	ft_skip_whitespace(&s);
	if (q)
		*q = s;
	tok = *s;
	if (*s == '|')
		s++;
	else if (*s == '<' || *s == '>')
		tok = ft_token_redir(&s, tok);
	else if (*s == 0)
		return (0);
	else
	{
		tok = 'c';
		while (*s != '\0' && !ft_strchr(*s, " \t\f\n\v\r") && !ft_strchr(*s, "|<>"))
			s++;
	}
	ft_skip_whitespace(&s);
	*ps = s;
	return (tok);
}
