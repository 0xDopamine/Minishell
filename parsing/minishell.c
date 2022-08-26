/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/26 12:34:12 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"
#include <readline/readline.h>

t_global g = { 0 };

int	ft_check_quotes_start(char *s)
{
	int	q_count;

	q_count = 0;
	if (*s == '"' || *s == '\'')
	{
		while ((*s == '"' || *s == '\'') && s)
		{
			q_count++;
			s++;
		}
	}
	return (q_count);
}

int	ft_check_quotes_end(char *s)
{
	int	q_count;
	int	len;

	q_count = 0;
	len = ft_strlen(s) - 1;
	if (s[len] == '"' || s[len] == '\'')
	{
		while ((s[len] == '"' || s[len] == '\'') && len >= 0)
		{
			q_count++;
			len--;
		}
	}
	return (q_count);
}

void	ft_check_quotes(char *s)
{
	int	q_count_front;
	int	q_count_back;

	q_count_front = ft_check_quotes_start(s);
	q_count_back = ft_check_quotes_end(s);
	if ((q_count_front > q_count_back)
		|| (q_count_front < q_count_back))	
	{
		perror("quotes error");
		//idk which exit code this should have but ill ask around
	}
}

int	ft_is_quoted(char *temp)
{
	if (*temp == 1 && temp)
		temp++;
	if ((*temp == '"' || *temp == '\'') && temp)
		temp++;
	if (*temp == 1 && temp)
		return (1);
	return (0);
}

int	ft_scan_unprintable(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

char	*null_terminate(char *q)
{
	int	i;

	i = 0;
	if (!q)
		return NULL;
	while (q[i])
	{
		if (q[i] == 1)
			q[i] = '\0';
		i++;
			q[i] = '1';
	}
	return (q);
}

char	*ft_del_end_squotes(char *s, int q_count)
{
	int	tail;
	int	len;

	len = ft_strlen(s);
	tail = len - 1;
	while (tail > 0 && s[tail])
	{
		if ((s[tail] == '\'' && q_count % 2 != 0) && s[tail] != '"')
			s[tail] = 1;
		else if ((s[tail] == '\'' || s[tail] == '"') && q_count % 2 == 0)
			s[tail] = 1;
		tail--;
	}
	printf("end s quotes: %s\n", s);
	return (s);
}

char	*ft_del_start_squotes(char *s)
{
	int		q_count;

	q_count = 0;
	while ((*s == '\'') && s)
	{
		q_count++;
		s++;
	}
	if (*s == '"' && q_count % 2 == 0 && s)
		s++;
	printf("end d quotes: %s\n", s);
	return (ft_del_end_squotes(s, q_count));
}
char	*ft_del_end_dquotes(char *s, int q_count)
{
	int	tail;
	int	len;

	len = ft_strlen(s);
	tail = len - 1;
	while (tail >= 0 && s[tail])
	{
		if ((s[tail] == '"' && q_count % 2 != 0) && s[tail] != '\'')
			s[tail] = '1';
		else if ((s[tail] == '\'' || s[tail] == '"') && q_count % 2 == 0)
			s[tail] = '1';
		tail--;
	}
	printf("end: %s\n", s);
	return (s);
}

char	*ft_del_start_dquotes(char *s)
{
	int		q_count;

	q_count = 0;
	while ((*s == '"') && s)
	{
		q_count++;
		*s = 1;
		s++;
	}
	if (*s == '\'' && q_count % 2 == 0 && s)
		s++;
	printf("start: %s\n", s);
	return (ft_del_end_dquotes(s, q_count));
}

void	ft_handle_quotes(char **q)
{
	char	*s;

	s = *q;
	ft_check_quotes(s);
	if (*s == '"')
		*q = ft_del_start_dquotes(s);
	else if (*s == '\'')
		*q = ft_del_start_squotes(s);
	printf("handling: %s\n", s);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		// rl_on_new_line();
		// write(1, "\n", 1);
		// rl_replace_line("", 0); /* comment all of this cuz we need to install brew and other things in goinfre */
		// rl_redisplay();
		g.exit_status = 130;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		g.exit_status = 0;
		return ;
	}
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
	printf("Two brothers minishell\n");
	//don't use CTRL -C signal now
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
	while (1)
	{
		line = readline("$> ");
		if (!line)
		{
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255); /* needs to be finished */
		}
		if (*line)
			add_history(line);
		// line = ft_strdup(spaces(line));
		simpleCommand = parsepipe(&line);
		ft_check_cmd(simpleCommand, env, &env_list);
		// system("leaks minishell");
		// demo(line);
	} 
	return 0;
}