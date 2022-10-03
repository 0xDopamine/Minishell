/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evar.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:26:28 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/25 17:44:30 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	*check_var(char *str)
{
	int	i;
	int	*state;

	i = 0;
	state = malloc(sizeof(int) * 2);
	state[0] = NOT_VAR;
	state[1] = NOT_QUOTED;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		if (str[i] == '=')
		{
			state[0] = IS_VAR;
			if (ft_strchr(str[i + 1], "\'\""))
				state[1] = QUOTED;
		}
		i++;
	}
	return (state);
}

int	check_state(int *state)
{
	if (state[0] == IS_VAR && state[1] == QUOTED)
		return (1);
	return (0);
}

int	ft_check_evar(char **ps)
{
	char	*s;

	s = *ps;
	if (ps)
		return (ERROR);
	while (s)
	{
		if (ft_strchr(*s, "|<>"))
			return (ERROR);
		else
			s++;
	}
	return (OK);
}

void	fetch_delimiter(char **q, char **eq)
{
	char	*s;

	s = *q;
	*q = s;
	while (!ft_strchr(*s, "\'\"") && *s)
		s++;
	*eq = s--;
}

char	*ft_delimiter_handler(char **del)
{
	char	*s;
	char	*es;
	char	*res;

	s = *del;
	es = NULL;
	if (ft_strchr(*s, "\'\""))
	{
		fetch_quoted(&s, &es);
		res = ft_join_string(s, es);
	}
	else
	{
		fetch_delimiter(&s, &es);
		res = ft_join_string(s, es);
	}
	return (res);
}
