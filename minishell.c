/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/08 02:49:43 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header.h"

char	*seperate_tokens(char *line)
{
	int		i;
	char	*token;
	
	i = 0;
	while (line[i] != ' ')
		i++;
	ft_strdup()
	

	sep = ft_split(line, ' ');
}

simpleCommands	*parse(char *line)
{
	int		i;
	char	*token;
	simpleCommands	*retrieve;
	char	*temp;

	i = 0;
	retrieve = ft_calloc(sizeof(Command) * 100000 + sizeof(char *), 1);
	while (token)
	{
		token = 
		retrieve->args[i] = token;
	}


}

ssize_t readin_prompt(const char* prompt, char **line, size_t *len) {
  fputs(prompt, stderr);
  return getline(line, len, stdin);
}

int	main(int argc, char **argv)
{
	char	*line;
	size_t	capacity;
	Command	*cmd;

	line = NULL;
	capacity = 0;
	while (readin_prompt("DopOS$>", line, capacity) > 0)
	{
		cmd = parse(line);

	}

	return 0;
}