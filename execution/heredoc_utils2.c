/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:20:33 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/17 17:21:42 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	ret = (char *)malloc(ft_strlen_char(str, '$') + 1);
	if (str[0] == '$')
		return (NULL);
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
