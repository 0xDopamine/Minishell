/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/17 04:17:04 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

int	*check_var(char *str)
{
	int	i;
	int	*state;

	i = 0;
	state = malloc(sizeof(int) * 2);
	state[0] = NOT_VAR;
	state[1] = NOT_QUOTED;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		if (str[i] == '=')
		{
			state[0] = IS_VAR;
			if (ft_strchr(str[i + 1], "\'\""))
				state[1] = QUOTED;
		}
		i++;
	}
	return (state);
}

int	check_state(int *state)
{
	if (state[0] == IS_VAR && state[1] == QUOTED)
		return (1);
	return (0);
}

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
			if (whitespaces[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// t_cmd	*ft_parse_heredoc(char **ps, t_env **env_list, t_cmd *cmd)
// {
// 	char	*delimiter;

// 	delimiter = *ps;
// 	env_list = NULL
// 	// ft_heredoc(env_list, cmd, delimiter);
// 	return (cmd);
// }

t_cmd	*parseexec(char **ps, t_env *env_list)
{
	char	*q;
	int		tok;
	int		argc;
	t_exec	*cmd;
	int		words;
	t_cmd	*ret;
	char	**split;
	int		*state;

	if (ft_strchr(**ps, "\'\""))
		words = num_words(*ps, 0);
	else
		words = num_words(*ps, 1);
	
	ret = execcmd(words);
	// for (int i = 0; i < 20; i++)
	// 	system("leaks minishell");
	cmd = (t_exec *)ret;
	argc = 0;
	ret = parseredir_test(ret, ps, env_list);
	while (!next(ps, "|"))
	{
		tok = get_token(ps, &q);
		if (tok == 0)
			break ;
		state = check_var(q);
		if (ft_strchr(*q, "\'\"") || check_state(state))
			split = ft_split_quotes(q, ' ');
		else
			split = ft_split(q, ' ');
		if (tok != 'c')
			printf("syntax error %c\n", tok); 
		cmd->argv[argc] = ft_ultimate_string_handler(&split[0], env_list, state);
		printf("cmd: %s\n", cmd->argv[argc]);
		argc++;
		if (argc >= words || split[1] == NULL)
			break ;
		ret = parseredir_test(ret, ps, env_list);
		if (ret == NULL)
			return (NULL);
	}
	cmd->argv[argc] = NULL;
	return (ret);
}

t_cmd	*parseredir_test(t_cmd *cmd, char **ps, t_env *env_list)
{
	int		tok;
	char	*q;
	char	**split;
	t_env	**list;
	t_redir	*head;
	//t_exec	*ex;

	list = malloc(sizeof(t_env **));
	*list = env_list;
	split = NULL;
	if (cmd->type == EXEC)
		head = NULL;
	if (cmd->type == REDIR)
		head = (t_redir *)cmd;
	while (next(ps, "<>"))
	{
		// printf("ps %s\n", *ps);
		tok = get_token(ps, 0);
		if (get_token(ps, &q) != 'c')
		{
			ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
			cmd = NULL;
			return (cmd);
		}
		// printf("q: %s\n", q);
		if (*q)
			split = ft_split(q, ' ');
		if (tok == '<')
			ft_lstadd_redir(&head, redircmd_test(cmd, split[0], O_RDONLY, STDIN_FILENO));
		else if (tok == '>')
			ft_lstadd_redir(&head, redircmd_test(cmd, split[0], O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
		else if (tok == 'A')
			ft_lstadd_redir(&head, redircmd_test(cmd, split[0], O_WRONLY | O_CREAT | O_APPEND, 1));
		else if (tok == 'H')
			ft_lstadd_redir(&head, redircmd_test(cmd, split[0], HEREDOC, 0));
		// while (head)
		// {	
		// 	head->cmd = cmd;
		// 	head = head->next;
		// }	
		// while (head)
		// {
		// 	if (head->cmd == EXEC)
		// 	{
		// 		ex = (t_exec *)head->cmd;
		// 		if (ex->argv[0])
		// 			head->
		// 	}
		// 	head = head->next;
		// }
		cmd = (t_cmd *)head;
		t_redir *redir = (t_redir *)cmd;

		printf("----file: %s\n", redir->file);
	}
	return (cmd);
}

int		ft_is_heredoc(char **ps)
{
	char	*q;
	int		i;

	i = -1;
	q = *ps;
	while (q[++i])
		if (q[i] == '<' && q[i + 1] == '<')
			return (1);
	return (0);
}

t_cmd	*parsepipe(char **ps, t_env *env_list)
{
	t_cmd	*cmd;
	
	cmd = parseexec(ps, env_list);
	if (cmd == NULL)
		return (NULL);
	// printf("ps: %s\n", *ps);
	if (next(ps, "|"))
	{
		get_token(ps, 0);
		cmd = pipecmd(cmd, parsepipe(ps, env_list));
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
	// if the char we stopped in at s, one of the chars we scanning for, if its true it returns true
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

int	get_token(char **ps, char **q)
{
	char	*s;
	int		tok;

	s = *ps;
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	if (q)
		*q = s;
	tok = *s;
	if (*s == '|')
		s++;
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			tok = 'H';
			s++;
		}
	}
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
		while (*s != '\0' && !ft_strchr(*s, " \t\f\n\v\r") && !ft_strchr(*s, "|<>"))
			s++;
	}
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	*ps = s;
	return (tok);
}
