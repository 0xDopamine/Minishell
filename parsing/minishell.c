/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/05 00:12:13 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "exec.h"
#include <readline/readline.h>

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simpleCommand;
	line = NULL;
	(void)argc;
	(void)argv;
	(void)env;
	simpleCommand = malloc(sizeof(t_cmd));
	// char **split;
	while (1)
	{
		line = readline("$>");
		if (line)
			add_history(line);
		line = ft_strdup(spaces(line));
		simpleCommand = parsepipe(&line);
		ft_check_cmd(simpleCommand);
		// demo(line);
	} 
	return 0;
}