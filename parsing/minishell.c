/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/18 01:15:39 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"
#include <readline/readline.h>

t_global	g = {0};

void	null_terminate(char **s)
{
	int		len;
	int		i;
	char	*q;

	i = -1;
	q = *s;
	len = ft_strlen(q);
	while (++i < len)
		q++;
	*q = '\0';
}

char	*ft_ultimate_string_handler(char **ps, t_env *env_list, int *state)
{
	char	*q;
	char	*eq;
	char	*res;
	int		dollars;

	dollars = 0;
	eq = NULL;
	res = NULL;
	(void)state;
	if (ps)
	{
		q = *ps;
		while (q)
		{
			if (ft_strchr(*q, "\'\""))
			{
				fetch_quoted(&q, &eq);
				if (*q == 1)
					return (NULL);
				if (*q == '$' && *eq != '\'')
				{					
					fetch_env(&q, &eq);
					if (*q == 1)
						return (NULL);
					q = ft_join_string(q, eq);
					res = ft_strjoin(res, ft_assign_env(q, env_list));
				}
				else if (*q == '\'' && (*(q + 1) == '$') && *eq == '"')
					res = ft_strjoin(res, ft_search_for_env(q, env_list));
				else
					res = ft_strjoin(res, ft_join_string(q, eq));
				if (*eq + 1)
					q = eq + 1;
			}
			else if (ft_strchr(*q, "$"))
			{
				ft_check_envs(&q);
				if (*q == '$')
				{	
					fetch_env(&q, &eq);
					q = ft_join_string(q, eq);
					if (*q == '$' && *(q + 1) == '\0')
						res = ft_strjoin(res, "$");
					else
						res = ft_strjoin(res, ft_assign_env(q, env_list));
					q = eq;
				}			
			}
			else
			{
				fetch_string(&q, &eq);
				res = ft_strjoin(res, ft_join_string(q, eq));
				if (*eq == '\0')
					break ;
				else
					q = eq;
			}
		}
	}
	if (res)
		*ps = res;
	return (*ps);
}

char	*ft_handle_quotes(char *q, t_env *env_list)
{
	char	*s;
	char	*res;
	char	*temp;
	int		i;

	s = q;
	(void)env_list;
	res = malloc(sizeof(char) * 10000000000);
	res[0] = 0;
	i = 0;
	while (s)
	{	
		if (*s && ft_strchr(*s, "\"\'"))
		{
			temp = s + 1;
			if (*temp != '\0' && *temp != *s)
			{
				while ((*temp != *s || !ft_strchr(*temp, "\'\"")) && *temp)
					res[i++] = *temp++;
				res[i] = '\0';
				if (*(temp) != '\0')
					s = temp + 1;
				else
					return (res);
			}
			else
				s++;
			while (*temp == *s && *s)
				s++;
		}
		else if (!ft_strchr(*s, "\"\'"))
		{
			temp = s;
			while (!ft_strchr(*temp, "\'\"") && *temp)
					res[i++] = *temp++;
			res[i] = '\0';
			if (*temp != '\0')
					s = temp;
			else
				return (res);
		}
		else
			s++;
	}
	return (res);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g.exit_status = 130;
		return ;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simple_command;
	t_env	*env_list;
	char	*temp;

	(void)argc;
	(void)argv;
	line = NULL;
	simple_command = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	printf("Two brothers minishell\n");
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		line = readline(CYAN"TwoBrosShell➤ "RESET);
		temp = line;
		if (!temp)
		{
			free(temp);
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255);
		}
		add_history(temp);
		temp = spaces(temp);
		simple_command = parsepipe(&temp, env_list);
		ft_check_cmd(simple_command, &env_list);
	}
	free(temp);
	freethis(&line);
	free(simple_command);
	return (0);
}
