/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/24 20:20:47 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "exec.h"
#include <readline/readline.h>

t_global g = { 0 };

//you can comment it here and in parseexec line 91 92

//handles quotes but not sure if its a parsing error or execution error

char	*null_terminate(char *q)
{
	int	i;

	i = 0;
	while (q[i])
	{
		if (q[i] == 1)
			q[i] = '\0';
		i++;
	}
	return (q);
}

char	*ft_del_end_quotes(char *s, int q_count)
{
	int	tail;
	int	len;

	len = ft_strlen(s);
	tail = len - 1;
	while (tail > len / 2)
	{
		if ((s[tail] == '"' && q_count % 2 != 0) && s[tail - 1] != '\'')
			s[tail] = 1;
		else if ((s[tail] == '\'' || s[tail] == '"') && q_count % 2 == 0)
			s[tail] = 1;
		tail--;
	}
	return (s);
}

char	*ft_double_quotes(char *s)
{
	int		q_count;

	q_count = 0;
	while ((*s == '"') && s)
	{
		q_count++;
		s++;
	}
	if (*s == '\'' && q_count % 2 != 0 && s)
		s--;
	else if (*s == '\'' && q_count % 2 == 0 && s)
		s++;
	return (ft_del_end_quotes(s, q_count));
}

void	ft_handle_quotes(char **q)
{
	char	*s;

	s = *q;
	if (*s == '"')
		*q = ft_double_quotes(s);
	printf("s: %s\n", *q);
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