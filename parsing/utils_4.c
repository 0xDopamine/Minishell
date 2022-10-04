/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:23:05 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/10/04 17:26:38 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*free_line_spaces(char *line)
{
	free(line);
	return (NULL);
}

char	*spaces_protection(char *line)
{
	if (!line)
		return (free_line_spaces(line));
	if (ft_strlen(line) == 1)
		return (ft_strdup(line));
	return (NULL);
}

char	*handle_spaces_return(char *line)
{
	line = handle_spaces(line);
	return (line);
}
