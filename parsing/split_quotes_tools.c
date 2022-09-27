/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 06:09:31 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/27 06:13:08 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

void	ft_quotes_case(char **split, char *str, t_split data)
{
	ft_split_quotes_case(split, str, data);
	ft_append_quoted_split(split, str, data);
}

void	ft_split_quotes_case(char **split, char *str, t_split data)
{
	data.tok = str[data.i];
	split[data.j][data.k++] = str[data.i];
	data.i++;
}

void	ft_append_quoted_split(char **split, char *str, t_split data)
{
	while (data.k < data.len && str[data.i]
		&& str[data.i] != data.tok)
		split[data.j][data.k++] = str[data.i++];
}

void	ft_split_protection(char **split)
{
	if (!*split)
	{
		freethis(split);
		return ;
	}
}
