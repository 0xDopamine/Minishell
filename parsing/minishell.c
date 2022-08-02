/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/02 14:06:08 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <readline/readline.h>


int	demo(char **ps, char **es, char **q)
{
	char	*s;
	int		tok;
	char	*eq;

	s = *ps;
	eq = *es;
	//move s into the first non whitespace
	while (s < eq && is_whitespace(s, eq))
		s++;
	if (q)
		*q = s;
	//collect return value
	tok = *s;
	if (*s == '|' || *s == '<')
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			tok = '+';
			s++;
		}
	} 
	else if (*s == 0)
		return (0);
	else
	{
		tok = 'c';
	//scan for the end of the token 
		while (s < eq &&  !is_whitespace(s, eq) && !is_symbol(s, eq))
			s++;
	}
	while (is_whitespace(s, eq))
		s++;
	*ps = s;
	return (tok);
} 

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
		printf("%s\n", line);
		if (line)
			add_history(line);
		simpleCommand = parsepipe(&line);
		
		// demo(line);
	} 
	return 0;
}