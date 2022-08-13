/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/13 19:24:31 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "exec.h"
#include <unistd.h>

int	num_words(char *str, int quote_flag)
{
	int		words;
	char	**split;
	int		i;

	words = 1;
	i = 0;
	if (quote_flag)
		split = ft_split(str, ' ');
	else
		split = ft_split_quotes(str, ' ');
	while(split[i++])
		words++;
	return (words);
}

int	is_whitespace(char *str, char *es)
{
	char	*whitespaces;
	int		i;
	int		j;

	whitespaces = ft_strdup("\n\t\r\v ");
	i = 0;
	es = NULL;
	while (str[i])
	{
		j = 0;
		while (whitespaces[j])
		{
			printf("%c\n", *str);
			if (whitespaces[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_cmd	*parseexec(char **ps)
{
	char	*q;
	int		tok;
	int		argc;
	t_exec	*cmd;
	int		words;
	// points to the tree we built so far
	t_cmd	*ret;
	char	**split;

	//create an exec node and allocate a blank node
	// *split = ft_strdup("");
	if (*ps[0] == '"')
		words = num_words(*ps, 0);
	else
		words = num_words(*ps, 1);
	ret = execcmd(words);
	cmd = (t_exec *)ret;
	argc = 0;
	ret = parseredir(ret, ps);
	// if its not pipe it might be an option or a file name
	while (!next(ps, "|"))
	{
		//dir lblan dial quotes f get token a lhmar ra dkchi 3lach kitbdl fin ki pointi q o ki pointi lrbk 3la - 
		tok = get_token(ps, 0, &q);
		if (tok == 0)
			break ;
		if (q[0] == '"')
			split = ft_split_quotes(q, ' ');
		else
			split = ft_split(q, ' ');
		if (tok != 'c')
			printf("syntax error\n");
		cmd->argv[argc] = split[0];
		if (argc >= words)
			break ;
		argc++;
		ret = parseredir(ret, ps);
	}
	cmd->argv[argc] = NULL;
	return (ret);
}

//parses redirs and returns a node in the tree
t_cmd	*parseredir(t_cmd *cmd, char **ps)
{
	int		tok;
	char	*q;

	while (next(ps, "<>"))
	{
		// returns the character it encounters '<' if < '+' if >> 
		tok = get_token(ps, 0, 0);
		if (get_token(ps, 0, &q) != 'c')
		{
			ft_putstr_fd("missing file for redirections\n", STDERR_FILENO);
			cmd->type = 0;
			return (cmd);
		}
		if (tok == '<')
			cmd = redircmd(cmd, q, O_RDONLY, STDIN_FILENO);
		else if (tok == '>')
			cmd = redircmd(cmd, q, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (tok == 'A')
			cmd = redircmd(cmd, q, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	// printf("redir q: %s\n", q);
	// printf("%d\n", cmd->type);
	return (cmd);
}

t_cmd	*parsepipe(char **ps)
{
	t_cmd	*cmd;

	cmd = parseexec(ps);
	if (next(ps, "|"))
	{
		get_token(ps, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps));
	}
	return (cmd);
}

int	ft_strchr(char s, char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == s)
			return (1);
		i++;
	}
	return (0);
}
// looks past any whitespace character and stops at first non whitespace char
int	next(char **ps, char *toks)
{
	char	*s;

	s = *ps;
	while (s && ft_strchr(*s, " \t\r\v\n\f"))
		s++;
	*ps = s;
	// is the char we stopped in at s, one of the chars we scanning for, if its true it returns true
	return (*s && ft_strchr(*s, toks));
}

int	is_symbol(char *str, char *es)
{
	char	*symbols;
	char	*temp;
	int		i;
	int		j;
	
	symbols = ft_strdup("<>|");
	temp = symbols;
	i = 0;
	es = NULL;
	while (str[i])
	{
		j = 0;
		symbols = temp;
		while (symbols[j])
		{
			if (str[i] == symbols[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_token(char **ps, char **es, char **q)
{
	char	*s;
	int		tok;

	(void)es;
	s = *ps;
	//move s into the first non whitespace
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	if (q)
		*q = s;
	//collect return value
	tok = *s;
	if (*s == '"')
	{
		*q = s;
		while (*s++)
			if (*s == '"')
				break ;
		s++;
		*ps = s;
		tok = 'c';
		return (tok);
	}
	if (*s == '|' || *s == '<')
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			tok = 'A';
			s++;
		}
	} 
	else if (*s == 0)
		return (0);
	else
	{
		tok = 'c';
	//scan for the end of the token 
		while (*s != '\0' && !ft_strchr(*s, " \t\f\n\v\r") && !ft_strchr(*s, "|<>"))
			s++;
	}
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	*ps = s;
	return (tok);
}