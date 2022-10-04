/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:32:21 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/10/04 19:00:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

void	ft_token_quotes(char **s, char **eq, int *tok)
{
	while (*s && ft_strchr(**s, "\'\""))
	{
		fetch_quoted(s, eq);
		if (!*s)
		{
			*tok = ERROR;
			break ;
		}
		if (*eq + 1)
			*eq += 1;
		*s = *eq;
	}
}

void	ft_skip_to_eos(char **s)
{
	char	*q;

	q = *s;
	while (*q != '\0' && !ft_strchr(*q, " \t\f\n\v\r")
		&& !ft_strchr(*q, "|<>"))
		q++;
	*s = q;
}

void	ft_get_token_conditions(char **ps, int *tok)
{
	char	*s;

	s = *ps;
	if (*s == '|')
		s++;
	else if (*s == '<' || *s == '>')
		*tok = ft_token_redir(&s, tok);
	else if (*s == 0)
		*tok = 0;
	else
	{
		*tok = 'c';
		ft_skip_to_eos(&s);
	}
	*ps = s;
}
