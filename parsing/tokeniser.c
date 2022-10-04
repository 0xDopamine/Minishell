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

int	ft_token_redir(char **s, int *tok)
{
	char	*p;

	p = *s;
	if (*p == '<')
	{
		p++;
		if (*p == '<')
			*tok = 'H';
		else if (*p == '>')
			*tok = ERROR;
		p++;
	}
	else if (*p == '>')
	{
		p++;
		if (*p == '>')
		{
			*tok = 'A';
			p++;
		}
		else if (*p == '<')
			*tok = ERROR;
	}
	*s = p;
	return (*tok);
}

void	ft_skip_whitespace(char **ps)
{
	char	*s;

	if (ps)
		s = *ps;
	else
		s = NULL;
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	*ps = s;
}

int	get_token(char **ps, char **q)
{
	char	*s;
	int		tok;
	char	*eq;

	s = *ps;
	eq = NULL;
	ft_skip_whitespace(&s);
	if (q)
		*q = s;
	tok = *s;
	ft_get_token_conditions(&s, &eq, &tok);
	if (s && ft_strchr(*s, "\"\'"))
		tok = ERROR;
 	ft_skip_whitespace(&s);
	*ps = s;
	return (tok);
}
