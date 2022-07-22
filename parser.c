/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/22 03:53:42 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*join_chars(char *curr, char *next)
{
	char	*value;

	value = ft_strdup("");
	value = ft_strjoin(curr, next);
	return (value);
}

t_cmd	*command_table(t_list *tokens)
{
	t_cmd	*simple_cmd;
	// int		next_type;
	// int		curr_type;
	int		i;
	char	*value;

	i = 0;
	value = ft_strdup("");
	simple_cmd = malloc(sizeof(t_cmd));
	simple_cmd->cmd = malloc(sizeof(char *) * 10000);
	while (tokens->next != NULL)
	{
		while (tokens->type == 6 && tokens->next->next != NULL)
		{
			value = ft_strjoin(value, tokens->content);
			if (tokens->next->type != 6)
			{
				simple_cmd->cmd[i] = ft_strdup(value);
				simple_cmd->type = 6;
			}
			tokens = tokens->next;
		}
		if (tokens->type == TOKEN_DASH)
		{
			simple_cmd->cmd[i] = ft_strdup("-");
			simple_cmd->type = 9;
		}
		else if (tokens->type == TOKEN_SPACE)
			tokens = tokens->next;
		else if (tokens->type == TOKEN_PIPE)
		{
			simple_cmd->cmd[i] = ft_strdup("|");
			simple_cmd->type = 0;
		}
		printf("%s\n", simple_cmd->cmd[i]);
		i++;
		tokens = tokens->next;
	}
	return (simple_cmd);
}