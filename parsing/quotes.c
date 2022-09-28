/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:08:56 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
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
	if (*s == '\0')
	{
		*q = NULL;
		ft_putstr_fd("Quotes error\n", NULL, STDERR_FILENO);
		g_var.exit_status = 256;
		return ;
	}
	*eq = s;
}

void	ft_check_quotes(char **str)
{
	char	*temp;
	char	*temp_eq;

	temp_eq = NULL;
	temp = *str;
	fetch_quoted(&temp, &temp_eq);
	if (temp == NULL)
		*str = NULL;
}
