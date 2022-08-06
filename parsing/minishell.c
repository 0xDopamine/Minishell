/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/06 16:11:30 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "exec.h"
#include <readline/readline.h>

t_global g = { 1, 0 };

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

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n$>", 3);
		g.exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		g.exit_status = 0;
		return ;
	}
	else
		exit(1);
	// readline("$>");
	return ;
}
int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simpleCommand;
	t_env 	*env_list;

	line = NULL;
	(void)argc;
	(void)argv;
	simpleCommand = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	// char **split;
	printf("Two brothers minishell\n");
	//there's a little problem with signal CTRL-C when a command get executed after it the line gets printed
	signal(SIGINT, ft_sig_handler);
	signal(EOF, ft_sig_handler);
	while (g.ifexit)
	{
		line = readline("$>");
		if (line)
			add_history(line);
		// line = ft_strdup(spaces(line));
		simpleCommand = parsepipe(&line);
		ft_check_cmd(simpleCommand, env, &env_list);
		// demo(line);
	} 
	return 0;
}